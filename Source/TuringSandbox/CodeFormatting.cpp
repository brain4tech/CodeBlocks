// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeFormatting.h"
#include <sstream>

FText UCodeFormatting::FormatText(FString InputPath) {
	UE_LOG(LogTemp, Warning, TEXT("Code Formatting: About to format from: \"%s\""), *InputPath);

	// build command
	// std::string Command = "bin\\clang-format-12.0.1_windows-amd64.exe --style=llvm input.txt";
	std::string Command = "bin\\clang-format-12.0.1_windows-amd64.exe --help";
	// Command += std::string(TCHAR_TO_UTF8(*InputPath));
	
	FString CommandString(Command.c_str());
	UE_LOG(LogTemp, Warning, TEXT("Code Formatting: Running Command: \"%s\""), *CommandString);

	// run command
	std::stringstream Output;
	Output << system(Command.c_str()) << std::endl;

	std::string OutputString = Output.str();
	FString OutputFString(OutputString.c_str());
	
	UE_LOG(LogTemp, Warning, TEXT("Code Formatting: Received output: \"%s\""), *OutputFString);

	// return output as FText
	const FString OutString(Output.str().c_str());
	return FText::FromString(OutString);
}

FString UCodeFormatting::SaveTextToFile(FString Content) {
	FString File = FPaths::ProjectConfigDir();
	File.Append(TEXT("input.txt"));
	if (FFileHelper::SaveStringToFile(Content, *File)) {
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Sucsesfuly Written: \"%s\" to the text file"),*File);
	}
	return *File;
}



