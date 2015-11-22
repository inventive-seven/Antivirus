/*
	Copyright (C) 2015 Kakorin Nikita
	Copyright (C) 2015 Zharkov Nikita
	Copyright (C) 2015 Betekhtin Artyoum
	Copyright (C) 2015 Korolev Evgeniy

	This file is part of Antivirus.

	Antivirus is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#ifndef ANTIVIRUS
#define ANTIVIRUS

//addiction list

#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <omp.h>
#include "yara.h"
/**
	@brief API antivirus

	Class for working with the methods of antivirus
*/
class Antivirus
{   
	/**
		@brief Checking existence of a directory

		@param[in] directoryNameToCheck Name of a checking directory
		@return true - if the directory exists, false - if directory doesn't exists
	*/
	bool isDirectoryExists(LPCWSTR directoryNameToCheck);


	/**
		@brief Checking existence of a file

		@param[in] directoryNameToCheck Name of a checking file
		@return true - if the file exists, false - if file doesn't exists
	*/
	bool isFileExists(LPCWSTR fileNameToCheck);


	/**
		@brief Convert a string of char to LPCWSTR
		@param[in] stringToConvert a pointer to an array of chars
		@return LPCWSTR string
	*/
	LPCWSTR charToLpcwstr(const char* stringToConvert);

	
	/**
		@brief Type of file from path
	*/
	enum PathTo { 
		PathToFolder,	///< The path to folder
		PathToFile,		///< The path to file
		NotExist 		///< The path to nonexist file
	};


	/**
		@brief Detect type of path to file

		@param[in] stringToCheck Path to file
		@return Type of path to file
	*/
	PathTo isPathToFile(const char* stringToCheck);


	/**
		@brief Open log-file
		@param[in] file Object of file

		The function open log-file stream
	*/
	void startLoging(std::ofstream &file);

	/**
		@brief Close log-file
		@param[in] file Object of file

		The function close log-file stream
	*/
	void endLoging(std::ofstream &file);
	
	
	/**
		@brief Write information about checked file
		@param[in] fileName Name of checked file
		@param[in] infected True if file infected

		Write information to log-file about checked file.
		Format: Date of checking file, path to file and filename, infected/safe
	*/
	void writeLog(const char* fileName, bool infected);
		
	/*out file for log's*/
	std::ofstream OutLog;

	/**
		@brief Get folder contain
		@param[in] path Path to folder
		@param[in] folders To this vector write folder list
		@param[in] files To this vector write file list

		Scan the path and return list of folders and files in the directory
	*/
	void GetFoldersAndFilesList(std::string path,
		std::vector<std::string> &folders,
		std::vector<std::string> &files);

	/**
		@brief Out wrap under YARA API

		This class make custom wrap under Yara library
	*/
	class SignatureAnalyzer
	{
	public:
		SignatureAnalyzer();
		~SignatureAnalyzer();
		/**
			@brief Start scan file
			@return  Type of result of scan file
		*/
		int Scanfile(const char *);
		/// brief Atavism, need to create base of signature
		char* SetLibrarry_file(char *);
	private:
		int ScanType; ///> Type of scanning
		char *Librarry_file; ///> Atavism
		/**
			@brief Function for set type of scan
		*/
		int SetScanType(int);		
		/**
			@brief Call back function

			Start after full scan file, detect type of infect and write info to log-file
		*/
		friend int callback_function_forfile(int, void*, void*);
	};

	/// Wrap under get Folders and Files list
	std::pair<std::vector<std::string>, std::vector<std::string>> SeeFilesFolders(const char*);

	/**
		@brief Get fullname of file
		@param[in] fName Name of file
		@param[in] inString Path to file
		@return Full name of file with full path
	*/
	std::string getFullNameFile(const std::string&, const char*)const;

	/**
		@brief Get fullname of folder
		@param[in] fName Name of folder
		@param[in] inString Path to the folder
		@return Full name of folder with full path
	*/
	std::string getFullNameFolder(const std::string&, const char*)const;

	SignatureAnalyzer analiz;


public:

	Antivirus(){}
	~Antivirus(){}

	/**
		@brief  Start scan the specified directory
		@param[in] inString Path to directory for scan

		This function starts scan the directory and uses std::cout for
		write out process information.
	*/
	void ToScan(const char* inString);


	/**
		@brief Function print message in output device
		@param[in] message Text of message

		The function uses std::output now
	*/
	static void outMessageToUser(const std::string&);


	/**
		@brief Check equal of two string
		@param[in] message First string
		@param[in] consoleArgument Second string
		@return true - if first string equals second string, else - false

		This function replaces operator '==' for two string
	*/
	static bool isThisCommand(const std::string&, const char*);


	/**
		@brief Returns current date and time
		@param[in] currentDateAndTimeStr
		@return Current date and time in string format
	*/
	char* getCurrentDateAndTime(char* currentDateAndTimeStr);


	/*constants implementation*/
	
	// The command for show help information
	const std::string helpArgumentString = "-help";
	/// The command for start check file or folder
	const std::string checkArgumentString = "-check";
	/// The command for start check system folders
	const std::string checkSystemFoulderArgumentString = "-checksys";
	/// The command for show information about programm
	const std::string infoArgumentString = "-info";

	/// Text of error with arguments number
	const std::string wrongArgumentsNumberErrorString = "\nWrong number of arguments. Use " + helpArgumentString + " for information.\n";

	/// Text of error with argument
	const std::string wrongArgumentsErrorString = "\nWrong arguments. Use " + helpArgumentString + " for information.\n";

	/// Help text
	const std::string helpOutputText = "\n" + checkArgumentString + " <path> - check file or directory\n" + 
									   checkSystemFoulderArgumentString + " - check system directory\n" +
									   infoArgumentString + " - about program\n";

	/// Information about programm
	const std::string infoOutputText = "\nAntivirus ver 0.0.1 Copyright(C) 2015\n" 
									   "This is free software, and you are welcome to redistribute\n"
									   "it under certain conditions.\n" 
									   "Program comes with ABSOLUTELY NO WARRANTY.\n"
									   "AMCP SPBU 2015\n";
	/// Text of error if path to file is not exists
	const std::string checkNoPathErrorText = "Please type path to file or directory to check.\n";

};
#endif

