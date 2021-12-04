#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

/* CS6210_TASK: Create your data structure here for storing spec from the config file */
struct MapReduceSpec {
	int n_workers;
	int n_output_files;
	int map_kilobytes;
	std::string output_dir;
	std::string user_id;
	std::vector<std::string> worker_ipaddr_ports;
	std::vector<std::string> input_files;
};

inline void split_and_insert(std::string input, std::vector<std::string>& output, char delimiter) {
	std::stringstream input_stream(input);
	std::string temp_string;

	while(getline(input_stream, temp_string, delimiter)) {
		output.push_back(temp_string);
	}
}

inline void populate_MapReduceSpec(std::vector<std::string> key_value, MapReduceSpec& mr_spec) {
	std::string key = key_value.at(0);
	std::string value = key_value.at(1);

	if (key.compare("n_workers") == 0) {
		mr_spec.n_workers = stoi(value);
	} else if (key.compare("worker_ipaddr_ports") == 0) {
		split_and_insert(value, mr_spec.worker_ipaddr_ports, ',');
	} else if (key.compare("input_files") == 0) {
		split_and_insert(value, mr_spec.input_files, ',');
	} else if (key.compare("output_dir") == 0) {
		mr_spec.output_dir = value;
	} else if (key.compare("n_output_files") == 0) {
		mr_spec.n_output_files = stoi(value);
	} else if (key.compare("map_kilobytes") == 0) {
		mr_spec.map_kilobytes = stoi(value);
	} else if (key.compare("user_id") == 0) {
		mr_spec.user_id = value;
	}
}

/* CS6210_TASK: Populate MapReduceSpec data structure with the specification from the config file */
inline bool read_mr_spec_from_config_file(const std::string& config_filename, MapReduceSpec& mr_spec) {
	std::ifstream config_file;
	std::string current_line;
	std::vector<std::string> key_value;
	config_file.open(config_filename);

	if (config_file.is_open()) {
		while(getline(config_file, current_line)) {
			split_and_insert(current_line, key_value,'=');
			populate_MapReduceSpec(key_value, mr_spec); 
			key_value.clear();
		}
		config_file.close();
		return true;
	} else {
		std::cout << "ERROR: UNABLE TO OPEN CONFIG FILE\n";
		return false;
	}
}


/* CS6210_TASK: validate the specification read from the config file */
inline bool validate_mr_spec(const MapReduceSpec& mr_spec) {
	if (mr_spec.n_workers < 1) {
		return false;
	} else if (mr_spec.worker_ipaddr_ports.size() < 1) {
		return false;
	} else if (mr_spec.input_files.size() < 1) {
		return false;
	} else if (mr_spec.output_dir.compare("") == 0) {
		return false;
	} else if (mr_spec.n_output_files < 1) {
		return false;
	} else if (mr_spec.map_kilobytes < 1) {
		return false;
	} else if (mr_spec.user_id.compare("") == 0) {
		return false;
	}

	return true;
}
