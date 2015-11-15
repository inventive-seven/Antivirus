#ifndef ANTIVIRUS
#define ANTIVIRUS

//addiction list

#include <windows.h>
#include <fstream>
#include "signature_analyzer.h"
#include <vector>
class Antivirus
{   
	bool isDirectoryExists(LPCWSTR directoryNameToCheck);

	bool isFileExists(LPCWSTR fileNameToCheck);

	LPCWSTR charToLpcwstr(const char* stringToConvert);

	enum PathTo{ PathToFolder, PathToFile, NotExist };

	/*return type of directory:file, folder,notexist */
	PathTo isPathToFile(const char* stringToCheck);

	/*open file stream*/
	void startLoging(std::ofstream &file);

	/*close file stream*/
	void endLoging(std::ofstream &file);
	
	/*write infected or not infected file*/
	void writeLog(const char* fileName, bool infected);
		
	/*out file for log's*/
	std::ofstream OutLog;

	void GetFoldersAndFilesList(std::string path,
		std::vector<std::string> &folders,
		std::vector<std::string> &files);
public:

	Antivirus(){}
	~Antivirus(){}

	/*check exist path and give next instructions*/
	void ToScan(const char* inString, signature_analyzer analiz);



	/*constants implementation*/
	
	const char *wrongArgumentsNumberErrorString = "Wrong number of arguments. Use \"-help\" for information.\n";

	const char *wrongArgumentsErrorString = "Wrong arguments. Use \"-help\" for information.\n";

	const char *helpArgumentString = "-help";

	const char *helpOutputText = "-check <path> - check file or directory\n"
								 "-checksys - check system directory\n"
								 "-info - about program\n";

	const char *infoArgumentString = "-info";

	const char *infoOutputText = "Antivirus ver. 0.0.1\n"
								 "AMCP SPBU 2015\n";

	const char *checkArgumentString = "-check";

	const char *checkNoPathErrorText = "Please type path to file or directory to check.\n";

	const char *checkSystemFoulderArgumentString = "-checksys";
};

char* getCurrentDateAndTime(char* currentDateAndTimeStr);

#endif

