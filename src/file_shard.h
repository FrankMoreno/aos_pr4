#pragma once

#include <vector>
#include "mapreduce_spec.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

/* CS6210_TASK: Create your own data structure here, where you can hold information about file splits,
     that your master would use for its own bookkeeping and to convey the tasks to the workers for mapping */
struct FileInfo {
     std::string file_name;
     int start;
     int end;
};

struct FileShard {
     std::vector<FileInfo> files;
};

inline void check_character(std::string file_name, int position) {
     FILE *pFile = fopen(file_name.c_str(), "r");
     fseek (pFile, position, SEEK_SET );
     int c = fgetc(pFile);
     std::cout << c << "\n";

     fclose (pFile);

}

inline int find_next_newline(std::string file_name, int position) {
     int offset = 0;
     FILE *pFile = fopen(file_name.c_str(), "r");
     fseek (pFile, position, SEEK_SET );
     int c = fgetc(pFile);
     while (c != '\n' && c != EOF) {
          c = fgetc(pFile);
          offset++;
     }

     fclose (pFile);

     return offset;
}
/* CS6210_TASK: Create fileshards from the list of input files, map_kilobytes etc. using mr_spec you populated  */ 
// Repeat for all input file
// Check if file is less than shard size
// If it is, add entire file to shard
// If not, add as much of the file until shard is full
inline bool shard_files(const MapReduceSpec& mr_spec, std::vector<FileShard>& fileShards) {
     FileShard list_of_files;
     int writtenCapacity = 0;
     int remaining_shard_capacity = mr_spec.map_kilobytes;
     int count = 0;

     for (std::string file_name : mr_spec.input_files) {
          int file_size = fs::file_size(file_name);
          int remaining_file_in_kilobytes = file_size / 1024;
          int pointer = 0;
          while (remaining_file_in_kilobytes > 0) {
               // If we can write entire file to shard, write it
               if (remaining_file_in_kilobytes < remaining_shard_capacity) {
                    FileInfo current_file_info;
                    current_file_info.start = pointer;
                    current_file_info.end = file_size - 1;
                    current_file_info.file_name = file_name;
                    list_of_files.files.push_back(current_file_info);
                    // std::cout << "Bucket: "<< count << " pushing " << pointer << " until " << file_size - 1 << " for file " << file_name << "\n";
                    remaining_shard_capacity -= remaining_file_in_kilobytes;
                    remaining_file_in_kilobytes = 0;
                    pointer = 0;
               // If not, fill up the rest of the shard and make a new one
               } else {
                    // std::cout << "Remaining shard capacity " << remaining_shard_capacity << "\n";
                    // std::cout << "Remaining file in kilobytes " << remaining_file_in_kilobytes << "\n"; 
                    FileInfo current_file_info;
                    current_file_info.file_name = file_name;
                    current_file_info.start = pointer;
                    // std::cout << "starting point is " << pointer << "\n";
                    pointer += remaining_shard_capacity * 1024;
                    // std::cout << "checking for next new line after " << pointer << "\n";
                    pointer += find_next_newline(file_name, pointer);
                    current_file_info.end = pointer;
                    // std::cout << "Bucket: "<< count << " pushing " << current_file_info.start << " until " << current_file_info.end << " for file " << file_name << "\n";
                    // std::cout << "Flushing shards\n";
                    remaining_file_in_kilobytes -= remaining_shard_capacity;
                    remaining_shard_capacity = mr_spec.map_kilobytes;
                    pointer++;
                    list_of_files.files.push_back(current_file_info);
                    fileShards.push_back(list_of_files);
                    list_of_files.files.clear();
                    count++;
               }
          }
          // std::cout << "Next file\n";
     }

     if (list_of_files.files.size() > 0) {
          fileShards.push_back(list_of_files);
     }

	return true;
}
