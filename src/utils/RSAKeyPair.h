#pragma once

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <iostream>
#include <memory>
#include <openssl/sha.h>
#include <vector>

class RSAKeyPair{
    public:
    std::string private_key_pem;
    std::string public_key_pem;

    RSAKeyPair(int bits = 2048) {
        generate_keypair(bits);
    }

    
    static bool verify(const std::string& private_key_pem, const std::string& public_key_pem) {
        const std::string message = "verify_test";

        // Load private key
        BIO* priv_bio = BIO_new_mem_buf(private_key_pem.data(), private_key_pem.size());
        std::unique_ptr<EVP_PKEY, decltype(&EVP_PKEY_free)> priv_key(
            PEM_read_bio_PrivateKey(priv_bio, nullptr, nullptr, nullptr), EVP_PKEY_free);
        BIO_free(priv_bio);
        if (!priv_key) return false;

        // Sign
        std::vector<unsigned char> signature;
        EVP_MD_CTX* sign_ctx = EVP_MD_CTX_new();
        size_t sig_len = 0;
        bool ok = false;

        if (EVP_DigestSignInit(sign_ctx, nullptr, EVP_sha256(), nullptr, priv_key.get()) &&
            EVP_DigestSignUpdate(sign_ctx, message.data(), message.size()) &&
            EVP_DigestSignFinal(sign_ctx, nullptr, &sig_len)) {
            signature.resize(sig_len);
            if (EVP_DigestSignFinal(sign_ctx, signature.data(), &sig_len)) {
                signature.resize(sig_len);
                ok = true;
            }
        }
        EVP_MD_CTX_free(sign_ctx);
        if (!ok) return false;

        // Load public key
        BIO* pub_bio = BIO_new_mem_buf(public_key_pem.data(), public_key_pem.size());
        std::unique_ptr<EVP_PKEY, decltype(&EVP_PKEY_free)> pub_key(
            PEM_read_bio_PUBKEY(pub_bio, nullptr, nullptr, nullptr), EVP_PKEY_free);
        BIO_free(pub_bio);
        if (!pub_key) return false;

        // Verify
        EVP_MD_CTX* verify_ctx = EVP_MD_CTX_new();
        ok = (EVP_DigestVerifyInit(verify_ctx, nullptr, EVP_sha256(), nullptr, pub_key.get()) &&
              EVP_DigestVerifyUpdate(verify_ctx, message.data(), message.size()) &&
              EVP_DigestVerifyFinal(verify_ctx, signature.data(), signature.size()) == 1);
        EVP_MD_CTX_free(verify_ctx);

        return ok;
    }

private:
    void generate_keypair(int bits) {
        EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_from_name(nullptr, "RSA", nullptr);
        if (!ctx) throw std::runtime_error("Failed to create RSA keygen context");

        if (EVP_PKEY_keygen_init(ctx) <= 0) {
            EVP_PKEY_CTX_free(ctx);
            throw std::runtime_error("Failed to initialize RSA keygen");
        }

        // Set key length
        OSSL_PARAM params[] = {
            OSSL_PARAM_construct_int("bits", &bits),
            OSSL_PARAM_construct_end()
        };
        if (EVP_PKEY_CTX_set_params(ctx, params) <= 0) {
            EVP_PKEY_CTX_free(ctx);
            throw std::runtime_error("Failed to set RSA params");
        }

        // Generate key
        EVP_PKEY* pkey_raw = nullptr;
        if (EVP_PKEY_generate(ctx, &pkey_raw) <= 0) {
            EVP_PKEY_CTX_free(ctx);
            throw std::runtime_error("RSA keygen failed");
        }
        EVP_PKEY_CTX_free(ctx);
        std::unique_ptr<EVP_PKEY, decltype(&EVP_PKEY_free)> pkey(pkey_raw, EVP_PKEY_free);

        // Export private key (PEM)
        BIO* priv_bio = BIO_new(BIO_s_mem());
        if (!PEM_write_bio_PrivateKey(priv_bio, pkey.get(), nullptr, nullptr, 0, nullptr, nullptr)) {
            BIO_free(priv_bio);
            throw std::runtime_error("Failed to export private key");
        }
        char* priv_data = nullptr;
        long priv_len = BIO_get_mem_data(priv_bio, &priv_data);
        private_key_pem.assign(priv_data, priv_len);
        BIO_free(priv_bio);

        // Export public key (PEM)
        BIO* pub_bio = BIO_new(BIO_s_mem());
        if (!PEM_write_bio_PUBKEY(pub_bio, pkey.get())) {
            BIO_free(pub_bio);
            throw std::runtime_error("Failed to export public key");
        }
        char* pub_data = nullptr;
        long pub_len = BIO_get_mem_data(pub_bio, &pub_data);
        public_key_pem.assign(pub_data, pub_len);
        BIO_free(pub_bio);
    }
};