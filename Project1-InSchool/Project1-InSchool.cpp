#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include "printTable.h"
#include "printMenu.h"
const std::string FILE_NAME_GROUP = "group.txt";
const std::string FILE_NAME_PROJECT = "project.txt";
const std::string FILE_OVERALL_STATISTIC = "Overall statistic.txt";
struct Group {
    std::string nameOfGroup;
    std::vector<std::string> nameOfStudentList;
    struct ProjectDateSubmitOfGroup {
        std::string projectSubmit;
        int dayOfSubmit, monthOfSubmit, yearOfSubmit;
        std::string statement;
    };
    std::vector<ProjectDateSubmitOfGroup*> projectDateSubmitOfGroupList;
    
};
struct Project {
    std::string nameOfProject;
    std::string shortDescriptionOfProject;
    int dayOfDeadLine;
    int monthOfDeadLine;
    int yearOfDeadLine;
};

struct HandleData {
    // Option 1:
    std::vector<Group*> listOfGroup;
    Group* group = new Group();

    void ReadFile() {
        std::ifstream groupFile(FILE_NAME_GROUP);
        std::string groupInformation;
        while (std::getline(groupFile, groupInformation)) {

            if (groupInformation.find("Group") != std::string::npos) {
                if (!group->nameOfGroup.empty()) {
                    Append(group);
                }
                group = new Group();
                group->nameOfGroup = groupInformation;
            }
            else {
                group->nameOfStudentList.push_back(groupInformation);
            }
        }
        if (!group->nameOfGroup.empty()) {
            Append(group);
        }
        groupFile.close();
    }
    void InputInformation() {
        group = new Group();
        std::vector<std::string> nameOfStudentEnteredList;
        int numberOfGroupAdd = 0;
        std::cout << "(!)Class already have " << listOfGroup.size() << " groups." << "\n";
        // Enter number of group need to add until greater than 0
        while (numberOfGroupAdd <= 0) {
            std::cout << "(-)Enter number of groups in the class you want to add: "; std::cin >> numberOfGroupAdd;
            std::cout << "-------------------------------------------------------------\n";
            if (numberOfGroupAdd <= 0) {
                std::cout << "(!) You need to enter the number of added groups greater than 0 . Please re-enter\n";
            }
        }
        int numberOfGroups = numberOfGroupAdd + listOfGroup.size();
        for (int i = listOfGroup.size(); i < numberOfGroups; i++) {
            group->nameOfGroup = "Group " + std::to_string(i + 1);
            int numberOfStudentInAGroup = 0;
            std::cout << "Enter information of group " << i + 1 << "\n";
            while (numberOfStudentInAGroup <= 0) {
                std::cout << "(-)Enter number of students: "; std::cin >> numberOfStudentInAGroup;
                if (numberOfStudentInAGroup <= 0) {
                    std::cout << "(!) You need to enter the number of added students greater than 0. Please re-enter\n";
                }
            }
            std::cin.ignore();
            for (int j = 0; j < numberOfStudentInAGroup; j++) {
                std::string nameOfStudent = "";
                bool isDuplicate = false;
                // enter number of student until not duplicate
                do {
                    isDuplicate = false;
                    std::cout << "(-)Enter name of student number " << j + 1 << ": ";
                    std::getline(std::cin, nameOfStudent);
                    for (auto group : listOfGroup) {
                        for (auto& nameOfStudentInList : group->nameOfStudentList) {
                            if (nameOfStudentInList == nameOfStudent) {
                                isDuplicate = true;
                                std::cout << "(!)Student already have in another group. Please re-enter\n";
                                break;
                            }
                        }
                        if (isDuplicate) {
                            break;
                        }

                    }
                    for (auto& nameOfStudentEntered : nameOfStudentEnteredList) {
                        if (nameOfStudentEntered == nameOfStudent) {
                            isDuplicate = true;
                            std::cout << "(!)Student already have in another group. Please re-enter\n";
                        }
                    }
                    if (!isDuplicate) {
                        group->nameOfStudentList.push_back(nameOfStudent);
                        nameOfStudentEnteredList.push_back(nameOfStudent);
                    }
                } while (isDuplicate);
            }
            std::cout << "-------------------------------------------------\n";
            listOfGroup.push_back(group);
            group = new Group();
            nameOfStudentEnteredList.clear();
        }
    }
    void SaveInformation() {
        std::ofstream groupFile(FILE_NAME_GROUP);
        for (auto group : listOfGroup) {
            groupFile << group->nameOfGroup << "\n";
            for (auto& nameOfStudent : group->nameOfStudentList) {
                groupFile << nameOfStudent << "\n";
            }
        }
    }
    void DisplayDataAllGroup() {
        printBorderOfTableGroup();
        printTopicOfTableGroup();
        printBorderOfTableGroup();

        int orderOfGroup = 1;
        
        for (auto group : listOfGroup) {
            int orderOfStudentInGroup = 1;
            for (auto& nameOfStudent : group->nameOfStudentList) {
                
                if (orderOfStudentInGroup == 1) {
                    printRowOfTableGroup(orderOfGroup, nameOfStudent);
                }
                else {
                    printRowOfTableGroup(nameOfStudent);
                }
                orderOfStudentInGroup++;
            }
            printBorderOfTableGroup();
            orderOfGroup++;
            
        }
    }
    void DisplayDataSingleGroup() {
        std::string nameOfGroup;
        std::cout << "Enter name of group: ";
        std::getline(std::cin, nameOfGroup);
        printBorderOfTableGroup();
        printTopicOfTableGroup();
        printBorderOfTableGroup();
        int orderOfGroup = 1;
        for (auto group : listOfGroup) {
            int orderOfStudentInGroup = 1;
            if (group->nameOfGroup == nameOfGroup) {
                for (auto& nameOfStudent : group->nameOfStudentList) {

                    if (orderOfStudentInGroup == 1) {
                        printRowOfTableGroup(orderOfGroup, nameOfStudent);
                    }
                    else {
                        printRowOfTableGroup(nameOfStudent);
                    }
                    orderOfStudentInGroup++;
                }
                printBorderOfTableGroup();
            } 
            orderOfGroup++;
        }
    }
    void Append(Group* group) {
        listOfGroup.push_back(group);
    }
    //Option 2
    Project* project = new Project();
    std::vector<Project*> listOfProject;
    //void ReadFileProject() {
    //    std::ifstream projectFile(FILE_NAME_PROJECT);
    //    std::string inforOfProject;
    //    while (std::getline(projectFile, inforOfProject)) {
    //        if (inforOfProject.find("Project") != std::string::npos) {
    //            if (!project->nameOfProject.empty()) {
    //                listOfProject.push_back(project);
    //            }
    //            project = new Project();
    //            project->nameOfProject = inforOfProject;               
    //        }
    //        else {
    //            project->shortDescriptionOfProject = inforOfProject;
    //            // Read the deadline information
    //            if (std::getline(projectFile, inforOfProject)) {
    //                int dayOfDeadline = std::stoi(inforOfProject);
    //                project->dayOfDeadLine = dayOfDeadline;
    //            }
    //            if (std::getline(projectFile, inforOfProject)) {
    //                int monthOfDeadLine = std::stoi(inforOfProject);
    //                project->monthOfDeadLine = monthOfDeadLine;
    //            }
    //            if (std::getline(projectFile, inforOfProject)) {
    //                int yearOfDeadLine = std::stoi(inforOfProject);
    //                project->yearOfDeadLine = yearOfDeadLine;
    //            }
    //        }
    //    }
    //    if (!project->nameOfProject.empty()) {
    //        listOfProject.push_back(project);
    //    }
    //    projectFile.close();
    //}
    void InputProjectInformation() {
        
        if (listOfProject.empty()) {
            int numberOfProject;
            std::cout << "Enter number of project: "; std::cin >> numberOfProject;

            for (int i = 1; i <= numberOfProject; i++) {
                std::cin.ignore();
                std::cout << "(*) Enter information of Project " << i << "\n";
                project->nameOfProject = "Project " + std::to_string(i);
                std::cout << "(+) Enter a short description about project: ";
                std::getline(std::cin, project->shortDescriptionOfProject);
                std::cout << "(-) Enter a submission deadline of project\n";
                std::cout << "(+) Enter day of deadLine: "; std::cin >> project->dayOfDeadLine;
                std::cout << "(+) Enter month of deadLine: "; std::cin >> project->monthOfDeadLine;
                std::cout << "(+) Enter year of deadLine: "; std::cin >> project->yearOfDeadLine;
                AppendProject(project);
                project = new Project();
            }
        }
        else {
            std::cout << "You have already " << listOfProject.size() << " :\n";
            std::cout << "Enter number of ";
        }
    }
    void DisplayInfProject() {
        if (listOfProject.empty()) {
            std::cout << "Not found any project\n";
        }
        for (const auto project : listOfProject) {
            std::cout << "Name of Project: " << project->nameOfProject << "\n";
            std::cout << "Description of project: " << project->shortDescriptionOfProject << "\n";
            std::cout << "Submission Deadline of project: " << project->dayOfDeadLine << "/" << project->monthOfDeadLine << "/" << project->yearOfDeadLine << "\n";
        }
    }
    void AppendProject(Project* project) {
        listOfProject.push_back(project);
    }
    //Option 3
    Group::ProjectDateSubmitOfGroup* projectDateSubmitGroup = new Group::ProjectDateSubmitOfGroup();
    void UpdateTimeToSubmitForSingleGroup() {
        if (listOfProject.empty()) {
            return;
        }
        bool isNameOfGroup = false;
        std::string nameOfGroup;
        do {
            std::cout << "Enter name of group you add submission date: ";
            std::getline(std::cin, nameOfGroup);
            for (const auto group : listOfGroup) {
                if (group->nameOfGroup == nameOfGroup) {
                    isNameOfGroup = true;
                }
            }
            if (!isNameOfGroup) {
                std::cout << "Not found any group. Please re-enter\n";
            }
        } while (!isNameOfGroup);
               
        bool isNameOfProject = false;
        std::string nameOfProject;
        do {
            std::cout << "Enter name of project you add submission date: ";
            std::getline(std::cin, nameOfProject);
            for (const auto project : listOfProject) {
                if (project->nameOfProject == nameOfProject) {
                    isNameOfProject = true;
                }
            }
            if (!isNameOfProject) {
                std::cout << "Not found any project. Please re-enter\n";
            }
            
        } while (!isNameOfProject);
        
                
        for (const auto group : listOfGroup) {
            if (group->nameOfGroup == nameOfGroup) {
                for (const auto projectDateSubmitGroup : group->projectDateSubmitOfGroupList) {             
                    if (projectDateSubmitGroup->projectSubmit == nameOfProject) {
                        std::cout << "(-) " << nameOfProject << ":\n";
                        std::cout << "(+) Enter day of submit: "; std::cin >> projectDateSubmitGroup->dayOfSubmit;
                        std::cout << "(+) Enter month of submit: "; std::cin >> projectDateSubmitGroup->monthOfSubmit;
                        std::cout << "(+) Enter year of submit: "; std::cin >> projectDateSubmitGroup->yearOfSubmit;
                    }                   
                    std::cin.ignore();
                    std::string optionEnterMoreIfor;
                    std::cout << "Do you want add more infomation for another groups(Y/N): ";
                    std::getline(std::cin, optionEnterMoreIfor);
                    if (optionEnterMoreIfor == "N") {
                        break;
                    }
                    else {
                        bool isNameOfProject = false;
                        do {
                            std::cout << "Enter name of project you add submission date: ";
                            std::getline(std::cin, nameOfProject);
                            for (const auto project : listOfProject) {
                                if (project->nameOfProject == nameOfProject) {
                                    isNameOfProject = true;
                                }
                            }
                            if (!isNameOfProject) {
                                std::cout << "Not found any project. Please re-enter\n";
                            }
                            if (nameOfProject == projectDateSubmitGroup->projectSubmit) {
                                isNameOfProject = false;
                                std::cout << "You already enter this group. Please re-enter\n";
                            }
                        } while (!isNameOfProject);
                    }
                }

            }
            
        }
    }
    void UpDateTimeToSubmitForAllGroup() {
        if (listOfProject.empty()) {
            std::cout << "You do not enter information for project, please do option 2 first\n";
            return;
        }
        for (const auto group : listOfGroup) {
            if (group->projectDateSubmitOfGroupList.empty()) {
                for (const auto project : listOfProject) {
                    projectDateSubmitGroup->projectSubmit = project->nameOfProject;
                    group->projectDateSubmitOfGroupList.push_back(projectDateSubmitGroup);
                    projectDateSubmitGroup = new Group::ProjectDateSubmitOfGroup();
                }
            }
            
        }
    }
    void DisplayDateOfSubmit() {
        for (const auto group : listOfGroup) {
            std::cout << "Submission of " << group->nameOfGroup << "\n";
            for (const auto dateSubmitProject : group->projectDateSubmitOfGroupList) {
                std::cout << "(-)" << dateSubmitProject->projectSubmit << ":\n";
                std::cout << "(+) Date submit: " << dateSubmitProject->dayOfSubmit << "/" << dateSubmitProject->monthOfSubmit << "/" << dateSubmitProject->yearOfSubmit << "\n";
            }
        }
    }
    // Option 4
    std::string stateOnTime = "On Time";
    std::string stateLate = "Late";
    std::string stateNotSubmit = "Not Yet Submitted";

    void HandleStateMent() {
        for (const auto group : listOfGroup) {
            for (const auto projectDateSubmitGroup : group->projectDateSubmitOfGroupList) {
                for (const auto project : listOfProject) {
                    if (project->nameOfProject == projectDateSubmitGroup->projectSubmit) {
                         if (projectDateSubmitGroup->dayOfSubmit == 0
                            || projectDateSubmitGroup->monthOfSubmit == 0
                            || projectDateSubmitGroup->yearOfSubmit == 0) {
                            projectDateSubmitGroup->statement = stateNotSubmit;
                         }
                        else if ((projectDateSubmitGroup->yearOfSubmit < project->yearOfDeadLine
                            || (projectDateSubmitGroup->yearOfSubmit == project->yearOfDeadLine
                                && projectDateSubmitGroup->monthOfSubmit < project->monthOfDeadLine)
                            || (projectDateSubmitGroup->yearOfSubmit == project->yearOfDeadLine
                                && projectDateSubmitGroup->monthOfSubmit == project->monthOfDeadLine
                                && projectDateSubmitGroup->dayOfSubmit <= project->dayOfDeadLine))) {
                            projectDateSubmitGroup->statement = stateOnTime;
                        }
                        else {
                            projectDateSubmitGroup->statement = stateLate;
                        }
                    }
                }
                
            }

        }
    }
    void DisplayStateOfProject() {
        if (listOfProject.empty()) {
            std::cout << "You do not update dealine for project. Please go back to option 2 before do that.\n";
            return;
        }
        std::string nameOfProject;
        std::cout << "(+) Enter name of project: "; std::getline(std::cin, nameOfProject);
        bool isFoundName = false;

        for (const auto project : listOfProject) {
            if (project->nameOfProject == nameOfProject) {
                isFoundName = true;
            }
        }
        if (!isFoundName) {
            std::cout << nameOfProject << " dose not exist\n";
            return;
        }
        printBorderOfTableProject();
        printBorderOfTableProject(1);
        printBorderDownLine();
        printTopicOfTableProject();
        printTopicOfTableProject(nameOfProject, 1);
        printColumnDownLine();
        printBorderOfTableProject();
        printBorderOfTableProject(1);
        printBorderDownLine();
        int orderOfGroup = 1;
        for (const auto group : listOfGroup) {
            int orderOfStudent = 1;
            for (const auto dateSubmitProjectOfGroup : group->projectDateSubmitOfGroupList) {
                if (dateSubmitProjectOfGroup->projectSubmit == nameOfProject) {
                    for (const auto& nameOfStudent : group->nameOfStudentList) {
                        if (orderOfStudent == 1) {
                            printRowOfTableProject(orderOfGroup, nameOfStudent);
                            printRowOfTableProject(dateSubmitProjectOfGroup->statement, 1);
                            printColumnDownLine();
                        }
                        else {
                            printRowOfTableProject(nameOfStudent);
                            printRowOfTableProject(1);
                            printColumnDownLine();
                        }                       
                        orderOfStudent++;
                    }
                    printBorderOfTableProject();
                    printBorderOfTableProject(1);
                    printBorderDownLine();
                    break;
                }
            }
            orderOfGroup++;
        }
        
    }
    void DisplayStateOfGroup() {
        if (listOfProject.empty()) {
            std::cout << "You do not update dealine for project. Please go back to option 2 before do that.\n";
            return;
        }
        std::string nameOfGroup;
        std::cout << "(+) Enter name of group: "; std::getline(std::cin, nameOfGroup);
        bool isFoundName = false;
        for (const auto group : listOfGroup) {
            if (group->nameOfGroup == nameOfGroup) {
                isFoundName = true;
            }
        }
        if (!isFoundName) {
            std::cout << nameOfGroup << " dose not exist\n";
            return;
        }
        printBorderOfTableProject();
        printBorderOfTableProject(listOfProject.size());
        printBorderDownLine();
        printTopicOfTableProject();
        for (const auto project : listOfProject) {
            printTopicOfTableProject(project->nameOfProject, listOfProject.size());
        }
        printColumnDownLine();
        printBorderOfTableProject();
        printBorderOfTableProject(listOfProject.size());
        printBorderDownLine();
        int orderOfGroup = 1;
        for (const auto group : listOfGroup) {
            int orderOfStudent = 1;
            if (group->nameOfGroup == nameOfGroup) {
                    for (const auto& nameOfStudent : group->nameOfStudentList) {
                        if (orderOfStudent == 1) {
                            printRowOfTableProject(orderOfGroup, nameOfStudent);
                            for (const auto dateSubmitProjectOfGroup : group->projectDateSubmitOfGroupList) {
                                printRowOfTableProject(dateSubmitProjectOfGroup->statement, listOfGroup.size());
                            }
                            printColumnDownLine();
                        }
                        else {
                            printRowOfTableProject(nameOfStudent);
                            for (const auto dateSubmitProjectOfGroup : group->projectDateSubmitOfGroupList) {
                                printRowOfTableProject(listOfProject.size());
                            }
                            printColumnDownLine();
                        }
                        orderOfStudent++;
                    }
                    printBorderOfTableProject();
                    printBorderOfTableProject(listOfProject.size());
                    printBorderDownLine();
                
                break;
            }           
            orderOfGroup++;
        }
        
    }
    // Option 5
    int day, month, year;
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::vector<Project*> projectValidList;
    void Statistic() {
        std::string option = "";
        std::cout << "(1) Enter specific day\n"
            <<"(2) Use current time\n";
        std::cout << "Enter the option: "; std::cin >> option;
        if (option == "1") {
            std::cout << "Enter day: "; std::cin >> day;
            std::cout << "Enter month: "; std::cin >> month;
            std::cout << "Enter year: "; std::cin >> year;
        }
        else if (option == "2") {
            day = ltm->tm_mday;
            month = 1 + ltm->tm_mon;
            year = 1900 + ltm->tm_year;
        }
        else {
            std::cout << "Invalid option. Please enter 1 or 2.\n";
            return; 
        }
        std::cin.ignore();
        std::cout << "The statement of projects having deadline before " << day << "/" << month << "/" << year << " is:\n";
        int numberOfProjectValid = 0;
        
        for (const auto project : listOfProject) {
            if ((year > project->yearOfDeadLine) ||
                (year == project->yearOfDeadLine && month > project->monthOfDeadLine) ||
                (year == project->yearOfDeadLine && month == project->monthOfDeadLine && day >= project->dayOfDeadLine)) {
                numberOfProjectValid++;
                projectValidList.push_back(project);
            }
        }
        printBorderOfTableProject();
        printBorderOfTableProject(numberOfProjectValid);
        printBorderDownLine();
        printTopicOfTableProject();
        for (const auto project : listOfProject) {
            if ((year > project->yearOfDeadLine) ||
                (year == project->yearOfDeadLine && month > project->monthOfDeadLine) ||
                (year == project->yearOfDeadLine && month == project->monthOfDeadLine && day >= project->dayOfDeadLine)) {
                printTopicOfTableProject(project->nameOfProject, numberOfProjectValid);
            }
            
        }
        printColumnDownLine();
        printBorderOfTableProject();
        printBorderOfTableProject(numberOfProjectValid);
        printBorderDownLine();
        int orderOfGroup = 1;
        for (const auto group : listOfGroup) {
            int orderOfStudent = 1;
            for (const auto& nameOfStudent : group->nameOfStudentList) {
                if (orderOfStudent == 1) {
                    printRowOfTableProject(orderOfGroup, nameOfStudent);
                    for (const auto projectValid : projectValidList) {
                        for (const auto dateSubmitProjectOfGroup : group->projectDateSubmitOfGroupList) {
                            if (projectValid->nameOfProject == dateSubmitProjectOfGroup->projectSubmit) {
                                printRowOfTableProject(dateSubmitProjectOfGroup->statement, numberOfProjectValid);
                            }
                            
                        }
                    }
                    
                    printColumnDownLine();
                }
                else {
                    printRowOfTableProject(nameOfStudent);
                    for (const auto projectValid : projectValidList) {
                        for (const auto dateSubmitProjectOfGroup : group->projectDateSubmitOfGroupList) {
                            if (projectValid->nameOfProject == dateSubmitProjectOfGroup->projectSubmit) {
                                printRowOfTableProject(numberOfProjectValid);
                            }

                        }
                    }
                    
                    printColumnDownLine();
                }
                orderOfStudent++;
            }
            printBorderOfTableProject();
            printBorderOfTableProject(numberOfProjectValid);
            printBorderDownLine();          
            orderOfGroup++;
        }
        
    }
    void OverallStatistic() {
        std::ofstream overallStatistic (FILE_OVERALL_STATISTIC);
        for (const auto group : listOfGroup) {
            overallStatistic << group->nameOfGroup << "\n";
            for (const auto projectValid : projectValidList) {
                for (const auto stateSubmitOfGroup : group->projectDateSubmitOfGroupList) {
                    if (projectValid->nameOfProject == stateSubmitOfGroup->projectSubmit) {
                        overallStatistic << stateSubmitOfGroup->projectSubmit << "\n" << stateSubmitOfGroup->statement << "\n";
                    }
                }
            }
            
        }

    }
    // Option 6

    void DisplayGroupSubmit() {
        std::cout << "Groups submit on time: ";
        for (const auto group : listOfGroup) {
            for (const auto inforDateSubmitOfGroup : group->projectDateSubmitOfGroupList) {
                if (inforDateSubmitOfGroup->statement == stateOnTime) {
                    std::cout << group->nameOfGroup << ", ";
                }
            }
        }
        std::cout << "\n";
    }
    void DisplayGroupNotSubmit() {
        std::cout << "Groups submit do not submit: ";
        for (const auto group : listOfGroup) {
            for (const auto inforDateSubmitOfGroup : group->projectDateSubmitOfGroupList) {
                if (inforDateSubmitOfGroup->statement == stateLate) {
                    std::cout << group->nameOfGroup << ", ";
                }
            }
        }
        std::cout << "\n";
    }
    //free memory
    //option 7
    void freeMomory() {
        delete group;
        delete project;
        listOfGroup.clear();
        listOfProject.clear();
    }
};
int main()
{
    HandleData* handleData = new HandleData();
    handleData->ReadFile();
    //handleData->ReadFileProject();
    std::string option;
    std::string option1OfMenu = "|(1) Group Information";
    std::string option2OfMenu = "|(2) Project deadline declaration";
    std::string option3OfMenu = "|(3) Project Date Submitssion";
    std::string option4OfMenu = "|(4) Statistic";
    std::string option5OfMenu = "|(5) Overall Statistic";
    std::string option6OfMenu = "|(6) Find groups do not complete or submit on time";
    std::string option7OfMenu = "|(7) Quit";
    std::cout << "\t\t\t\t\t\t\t\t" << "MENU" << "\n";
    while (true) {
        printRowMenu();
        std::cout << "\t\t\t\t\t" <<std::left << std::setfill(' ') << std::setw(50) << option1OfMenu << "|" << "\n";
        printRowMenu();
        std::cout << "\t\t\t\t\t" << std::left << std::setfill(' ') << std::setw(50) << option2OfMenu << "|" << "\n";
        printRowMenu();
        std::cout << "\t\t\t\t\t" << std::left << std::setfill(' ') << std::setw(50) << option3OfMenu << "|" << "\n";
        printRowMenu();
        std::cout << "\t\t\t\t\t" << std::left << std::setfill(' ') << std::setw(50) << option4OfMenu << "|" << "\n";
        printRowMenu();
        std::cout << "\t\t\t\t\t" << std::left << std::setfill(' ') << std::setw(50) << option5OfMenu << "|" << "\n";
        printRowMenu();
        std::cout << "\t\t\t\t\t" << std::left << std::setfill(' ') << std::setw(50) << option6OfMenu << "|" << "\n";
        printRowMenu();
        std::cout << "\t\t\t\t\t" << std::left << std::setfill(' ') << std::setw(50) << option7OfMenu << "|" << "\n";
        printRowMenu();
        std::cout << std::endl;
        std::cout << "Enter your option: ";
        std::getline(std::cin, option);
        if (option == "1") {
            std::string optionOf1 = "";
            std::cout << "(1) Input information of groups\n"
                << "(2) Display information\n"
                << "(3) Save groups information\n";
            std::cout << "Enter your option: ";
            std::getline(std::cin, optionOf1);
            if (optionOf1 == "1") {
                handleData->InputInformation();
            }
            else if (optionOf1 == "2") {
                std::string optionOf1_2 = "";
                std::cout << "(1) Display information for all group\n"
                     << "(2) Display information for specific group\n";
                std::cout << "Enter your option: "; std::getline(std::cin, optionOf1_2);
                if (optionOf1_2 == "1") {
                    handleData->DisplayDataAllGroup();
                }
                else if (optionOf1_2 == "2") {             
                    handleData->DisplayDataSingleGroup();
                }
            }
            else if (optionOf1 == "3") {
                handleData->SaveInformation();
            }
        }
        //Option 2
        else if (option == "2") {
            std::string optionOf2;
            std::cout << "(1) Input Projects Information\n"
                << "(2) Display Information of Groups\n";
            std::cout << "Enter your option: ";
            std::getline(std::cin, optionOf2);
            if (optionOf2 == "1") {
                handleData->InputProjectInformation();
                handleData->UpDateTimeToSubmitForAllGroup();
                handleData->HandleStateMent();
                std::cin.ignore();
            }
            else if (optionOf2 == "2") {
                handleData->DisplayInfProject();
            }
        }
        //Option 3
        else if (option == "3") {
            std::string optionOf3;
            std::cout << "(1) Input Project Date Submit's Groups\n"
                << "(2) Display Information of Date Submit's Groups\n";
            std::cout << "Enter your option: ";
            std::getline(std::cin, optionOf3);
           // handleData->UpDateTimeToSubmitForAllGroup();
            if (optionOf3 == "1") {
                handleData->UpdateTimeToSubmitForSingleGroup();
                handleData->HandleStateMent();
                
            }
            else if (optionOf3 == "2") { 
                handleData->DisplayDateOfSubmit();
            }
            
        }
        else if (option == "4") {
            std::string optionOf4;
            std::cout << "(1) Display Statement of project\n"
                << "(2) Display Information of Date Submit's Groups\n";
            std::cout << "Enter your option: ";
            std::getline(std::cin, optionOf4);
            handleData->HandleStateMent();
            if (optionOf4 == "1") {
                handleData->DisplayStateOfProject();
            }
            else if (optionOf4 == "2") {
                handleData->DisplayStateOfGroup();
            }
        }
        else if (option == "5") {
            
            std::string optionOf5;
            std::cout << "(1) Overall Statistic\n"
                <<"(2) Export overall statistic\n";
            std::cout << "Enter your option: "; std::getline(std::cin, optionOf5);
            if (optionOf5 == "1") {
                handleData->Statistic();
            }
            else if (optionOf5 == "2") {
                handleData->OverallStatistic();
            }
        }
        else if (option == "6") {
            std::string optionOf6;
            std::cout << "(1) Display Groups submit on time\n"
                << "(2) Display Groups submit late\n";
            std::cout << "Enter your option: ";
            std::getline(std::cin, optionOf6);
            handleData->HandleStateMent();
            if (optionOf6 == "1") {
                handleData->DisplayGroupSubmit();
            }
            else if (optionOf6 == "2") {
                handleData->DisplayGroupNotSubmit();
            }
        }
        else if (option == "7") {
            std::string optionOf7;
            std::cout << "Do you want to quite program(Y/N): "; std::getline(std::cin, optionOf7);
            if (optionOf7 == "Y") {
                handleData->freeMomory();
                break;
            }
            
        }
        std::cout << "(*)Press enter to back to menu...";
        //std::cin.ignore();
        std::getline(std::cin, option);
        system("cls");
    }
    // free memory
    delete handleData;
}

