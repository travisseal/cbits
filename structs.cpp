/* 
 * This is the driver program for connecting to a file
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>


using namespace std;


struct Task
{
private:
    
    static const int arraySize = 101;
    
    char courseName[arraySize];
    char courseDescription[arraySize];
    char courseDate[arraySize];
    
public:
    
    //constructor
    
    Task()
    {
        initialize();
    }
    
    //initialize all the arrays
    void initialize()
    {
        for(int index = 0; index < arraySize; index++)
        {
            courseName[index] = '\0';
            courseDescription[index] = '\0';
            courseDate[index] = '\0';
        }   
    }
    
    // getters
    
    const char* getCourseName() 
    {
        return courseName;
    }
    
    const char* getDescription()
    {
        return courseDescription;
    }
    
    const char* getDate()
    {
        return courseDate;
    }
    
    
    /*
     
        These are the 3 main inputs into the task
     
    */
    
    //setter
    void setCourseName(char in_courseName[])
    {
        strcpy(courseName,in_courseName);
       
    }
    
    //setter
    void setCourseDescription(char in_Description[])
    {
        strcpy(courseDescription,in_Description);
       
    }
    
    //setter
    void setCourseDate(char in_Date[])
    {
        strcpy(courseDate,in_Date);
       
    }
    
    
};


// This is the main data store. The type is Task, and thus only stores tasks into its task array.

struct DataStore
{

private:
    
    
    int counter = 0;
    
    Task tasks[100];
    //number of tasks we have added, also used as the index in the array
    
    
public:
   
    DataStore()
    {
        cout << "some created me!" << "\n";
                
    }
    
    Task addTask(Task newTask)
    {
        
       tasks[counter] = newTask;
       
       counter++;
    }
    
    Task getAllTasks()
    {
        cout << "\n";
        cout << "\n";
        cout << "Current task list";
        cout << "Current size is " << counter;
        
        for(int index = 0; index < counter; index++)
        
        {
                cout << "\n";
                cout << "\n";
                
                cout << "course: " << tasks[index].getCourseName() << "\n";
                cout << "description: " << tasks[index].getDescription() << "\n";
                cout << "date: " << tasks[index].getDate() << "\n";
                
                cout << "\n";
                cout << "\n";
                
        }
    }
    
};

/*
 * 
 * This is probably bad programming here, however, I could not avoid creating a global datastore without a class
 */

DataStore dataStore;

/*
 This is a  c++ struct  generator that creates new tasks. Three inputs are required:
 * 1) Char array courseDescription, 2)char array name, 3) and char array date. 
 * These are required fields
 * Any object that calls this entity and passes the right parameters to the in constructor
 * will create a new task.
 * 
 * The generator 'has-a' data store, that stores Task objects. 
 
 */

struct TaskGenerator
{
    
     DataStore buildTask(char courseDescription[],char name[], char date[])
     {
        
        Task myTask;
       
        //cout << "Item created: " << name;
        
        myTask.setCourseName(name);
        myTask.setCourseDescription(courseDescription);
        myTask.setCourseDate(date);
        
        dataStore.addTask(myTask);
        //add the new task to the list of tasks
        
        return dataStore;
    }
    
    
};

/*
 *This c++ struct that handles file input and output. This struct will instantiate TypeGenerator, and thus automatically builds task
 * objects from the data source.
 */
struct FileIO 
{
    private:
        
         ofstream outFile;

         ifstream inFile;
         
    public:
        
        
        //function writes to the file specified

        void writeFile(char filePath[])
        {


            outFile.open(filePath);
            outFile << "Structs are like classes, only public" << "\n";
            outFile.close();

        }

        //function reads the specified file and parse into variables

        DataStore readFile(char filePath[])
        {
            const int arraySize = 200;
            
            TaskGenerator taskBuilder;
            
            char courseName[arraySize];
            char courseDescription[arraySize];
            char courseDate[arraySize];
    
            
            inFile.open(filePath);
            
            while (!inFile.eof()) 
            {
                //this reads the first record
                inFile.getline(courseName, 500, ';');
                inFile.getline(courseDescription, 500, ';');
                inFile.getline(courseDate, 500, '\n');
                inFile.get();//read left over garbage
                
                //this is a new task item
                  dataStore = taskBuilder.buildTask(courseDescription,courseName,courseDate);
                 
                //debug code
                 
               // cout << "course: " << courseName << "\n";
                //cout << "description: " << courseDescription << "\n";
               // cout << "date: " << courseDate << "\n";
                  
                  
            }
            
            inFile.close();
            
            return dataStore;
        }
        
        
};

//user interface 

//**NEED TO RECONSTRUCT THIS**
struct UserInterface
{
    
public:
    
    
    
    UserInterface(DataStore TaskList)
    {
        dataStore = TaskList;
        
        while(isRunning)
        {
            PrintWelcomeScreen();
        }

    }

private:
    
    bool isRunning = true;
    
    char userOption;
    char courseName[101];

    struct OptionSelector
    {
        TaskGenerator addTask;

        char courseName[101]; 
        char taskDescription[101];
        char date[101];

        void initialize()
        {
            for(int index = 0; index < 101; index++)
            {
                courseName[index] = '\0';
            }
        }


        OptionSelector(char * userOption, DataStore data)
        {
           
                initialize();


                if(*userOption == 'a')
                {
                    cout << " enter course name (less than 101 characters): ";

                    cin.clear();
                    cin.sync();

                    cin.getline(courseName,101,'\n');

                    cout << "Enter task description): ";
                    cin.getline(taskDescription,101,'\n');

                    cin.clear();
                    cin.sync();

                    cout << "Enter date): ";
                    cin.getline(date,101,'\n');

                    cin.clear();
                    cin.sync();

                    cout << "before add task: " << "\n";
                    //addTask.dataStore.getAllTasks();
                    
                    //create the task
                     addTask.buildTask(taskDescription,courseName,date);

                }

                if(*userOption == 's')
                {
                    //show the added item
                    data.getAllTasks();
                }

                if(*userOption == 'q')
                {
                    
                }

            
        }
    };
   
    
    void  PrintWelcomeScreen()
    {
         cout << "Welcome to my Task List:" << "\n";
         cout << "(a) to add a task" << "\n";
         cout << "(s) to show the task list" << "\n";
         cout << "(f) to find a task by course name" << "\n";
         cout << "(q) to quit" << "\n";
         
         cout << "\n";
         
         cout << "Please enter an option : " << "\n";
         
         cin.get(userOption);
         cin.get(); // eat the new line char in the buffer
         cin.clear();
         cin.sync();

         //send user selected option to the option handler along with the data store
         OptionSelector selectChoice(&userOption,dataStore);
          
    }
    
 

};




int main() {
    

    FileIO inFile;
    
    //return a struct and pass it into th gui
    
    
    UserInterface GUI(inFile.readFile("/Users/tseal/Desktop/records.txt"));
    
    

    return 0;
}