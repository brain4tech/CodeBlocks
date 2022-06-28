// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFormatting.h"
#include <sstream>

FString UCodeFormatting::SaveTextToFile(FString Content) {
	FString File = FPaths::ProjectConfigDir();
	File.Append(TEXT("input.txt"));
	if (FFileHelper::SaveStringToFile(Content, *File)) {
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Sucsesfuly Written: \"%s\" to the text file"),*File);
	}
	return *File;
}

FText UCodeFormatting::FormatText(FString InputPath) {
	UE_LOG(LogTemp, Warning, TEXT("Code Formatting: About to format from: \"%s\""), *InputPath);

	// prepare input-directory
	std::string InputDir = std::string(TCHAR_TO_UTF8(*InputPath));
	#ifdef _WIN32
			size_t pos;
			while ((pos = InputDir.find("/")) != std::string::npos) {
				InputDir.replace(pos, 1, "\\");
			}
	#endif

	#ifdef __linux__
		int stringpos = -3;
		while (true){
			stringpos = InputDir.find(" ", stringpos + 3);

			if (stringpos == std::string::npos){
				break;
			}
			InputDir.replace(stringpos, 1, "\\ ");
		}


	#endif

	#ifdef __APPLE__
		int stringpos = -3;
		while (true){
			stringpos = InputDir.find(" ", stringpos + 3);

			if (stringpos == std::string::npos){
				break;
			}
			InputDir.replace(stringpos, 1, "\\ ");
		}


	#endif

	// prepare execution directory
	FString TempExecDir = FPaths::ProjectDir();
	std::string Command = "";

#ifdef _WIN32
		TempExecDir.Append("Source/TuringSandbox/bin/clang-format-12.0.1_windows-amd64.exe");
		std::string ExecDir = std::string(TCHAR_TO_UTF8(*TempExecDir));
		
		while ((pos = ExecDir.find("/")) != std::string::npos) {
			ExecDir.replace(pos, 1, "\\");
		}
		

		// build command for windows
		Command = "\"\"" + ExecDir + "\" --style=llvm -i \"" + InputDir + "\"\"";
#endif

#ifdef __linux__
		// build command for linux
		stringpos = -3;
	
		TempExecDir.Append("Source/TuringSandbox/bin/clang-format-12.0.1_linux-amd64");
		std::string ExecDir = std::string(TCHAR_TO_UTF8(*TempExecDir));

		while (true){
			stringpos = ExecDir.find(" ", stringpos + 3);

			if (stringpos == std::string::npos){
				break;
			}
			ExecDir.replace(stringpos, 1, "\\ ");
		}

		Command = ExecDir + " --style=llvm -i " + InputDir;

#endif

#ifdef __APPLE__
		// build command for mac
		stringpos = -3;
	
		TempExecDir.Append("Source/TuringSandbox/bin/clang-format-12.0.1_macosx-amd64");
		std::string ExecDir = std::string(TCHAR_TO_UTF8(*TempExecDir));

		while (true){
			stringpos = ExecDir.find(" ", stringpos + 3);

			if (stringpos == std::string::npos){
				break;
			}
			ExecDir.replace(stringpos, 1, "\\ ");
		}
	
		// Command = ExecDir + " --style=llvm -i " + InputDir;
		Command = "./" + ExecDir + " --style=llvm -i " + InputDir;
#endif
	
	// log command
	FString CommandString(Command.c_str());
	UE_LOG(LogTemp, Warning, TEXT("Code Formatting: Running Command: \"%s\""), *CommandString);

	// run command
	system(Command.c_str());

	// fetch the result
	FString FileContent;
	FFileHelper::LoadFileToString(FileContent, *InputPath,FFileHelper::EHashOptions::None);

	// return output as FText
	return FText::FromString(FileContent);
}



