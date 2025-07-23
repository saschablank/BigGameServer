#pragma once
#include <string>
#include <vector>
#include <map>
#include <string_view>



class Helper {
public:
    static std::vector<std::string_view> split(std::string_view str, char delimiter) {
        std::vector<std::string_view> result;
        size_t start = 0;

        while (start < str.size()) {
            size_t end = str.find(delimiter, start);
            if (end == std::string_view::npos)
                end = str.size();
            result.emplace_back(str.substr(start, end - start));
            start = end + 1;
        }

        return result;
    }


    static std::map<std::string, std::string> parseCommandLineArgs(int argc, char* argv[]) {
        std::map<std::string, std::string> args;
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg.find("--") == 0) {
                size_t pos = arg.find('=');
                if (pos != std::string::npos) {
                    std::string key = arg.substr(2, pos - 2);
                    std::string value = arg.substr(pos + 1);
                    args[key] = value;
                } else {
                    args[arg.substr(2)] = ""; // No value provided
                }
            }
        }
        return args;
    }
    

    static std::map<std::string, std::string> get_env_variables() {
        std::map<std::string, std::string> env_vars;
        return env_vars;
    }

    static std::string string_map_to_json_str(std::map<std::string, std::string> map) {
        std::string json_str = "{";
        for (const auto& pair : map) {
            if (json_str.size() > 1) {
                json_str += ",";
            }
            json_str += "\"" + pair.first + "\":\"" + pair.second + "\"";
        }
        json_str += "}";
        return json_str;
    }

    static std::map<std::string,std::string> ReadReqBodyParameters(const std::string& request_body, char split_char_parameter='&', char split_char_value_pairs='=') {
        std::vector<std::string_view> parameters_split = Helper::split(request_body, split_char_parameter);
        std::map<std::string,std::string> body_values;
        for( const auto& parameter_field : parameters_split ){
            std::vector<std::string_view> parameters_split = Helper::split(parameter_field, split_char_value_pairs);
            if(parameters_split.size() > 1){
                body_values[std::string(parameters_split[0])] = std::string(parameters_split[1]);
            }
        }
        return body_values;
    }
};