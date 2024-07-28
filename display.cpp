
#include "Parking_System.h"

// Function to display the availability of parking slots
void display()
{
    FILE *fptr = fopen("parking_log.txt", "r");
    if (!fptr) 
    {
	cerr << "UNABLE  TO OPEN FILE" << endl;
	return;
    }

    char ch;
    cout << "--------------------------------" << endl;
    cout << "AVAILABILITY OF SLOTS FOR PARKING" << endl;
    cout << "--------------------------------" << endl;
    for (int i = 0; i < 10; i++) 
    {
	cout << "SLOT   " << i + 1;
	ch = fgetc(fptr);
	if (ch == '0') 
	{
	    cout << "     AVAILABLE " << endl;
	} else if (ch == '1') 
	{
	    cout << "     OCCUPIED " << endl;
	}
    }
    fclose(fptr);
}

// Function to park a car in an available slot
void park_car()
{
    FILE *fptr = fopen("parking_log.txt", "r+");
    if (!fptr)
    {
	cerr << "UNABLE TO OPEN FILE" << endl;
	return;
    }

    char ch;
    char ID[6]; // ID should be 5 characters + null terminator
    int i;
    FILE *file = fopen("Id.txt", "r+");
    if (!file)
    {
	cerr << "UNABLE TO OPEN ID FILE" << endl;
	fclose(fptr);
	return;
    }

    // Find the first available slot
    for (i = 0; i < 10; i++)
    {
	fseek(fptr, i, SEEK_SET);
	ch = fgetc(fptr);
	if (ch == '0')
	{
	    fseek(fptr, i, SEEK_SET); // Move back to update the slot
	    fputc('1', fptr);

	    cout << "ENTER THE UNIQUE ID (5 characters): ";
	    cin >> ID;

	    // Ensure ID is exactly 5 characters long
	    if (strlen(ID) != 5)
	    {
		cerr << "ID MUST BE IN 5 CHARACTERS." << endl;
		fclose(fptr);
		fclose(file);
		return;
	    }

	    // Move to the correct line in the ID file
	    fseek(file, 0, SEEK_SET);
	    char temp[30];
	    for (int j = 0; j < i; j++)
	    {
		fgets(temp, sizeof(temp), file); // Skip lines
	    }

	    // Write the ID to the correct line in the ID file
	    fprintf(file, "%-5s\n", ID);
	    fflush(file);
	    break;
	}
    }

    if (i < 10)
    {
	cout << "SLOT " << i + 1 << " IS NOW OCCUPIED" << endl;
    }
    else
    {
	cout << "ALL SLOTS ARE ALREADY OCCUPIED" << endl;
    }
    fclose(fptr);
    fclose(file);
}

void exit_car()
{
    FILE *fptr = fopen("parking_log.txt", "r+");
    if (!fptr) 
    {
	cerr << "UNABLE TO OPEN FILE" << endl;
	return;
    }

    int slot;
    char pass[6]; // ID should be 5 characters long plus null terminator
    char temp[30],ch; // Array to store IDs of 10 slots

    cout << "--------------------------------" << endl;
    cout << "ENTER THE  SLOT NUMBER TO EXIT: ";
    cin >> slot;
    cout << "--------------------------------" << endl;
    slot--; // Convert to zero-based index
    cout << "ENTER  YOUR UNIQUE ID (Must be 5 characters) :" << endl;
    scanf("%s", pass);
    if (strlen(pass) != 5)
    {
	cerr << "ID MUST BE  IN  5 CHARACTERS ." << endl;
	fclose(fptr);
	return;
    }

    FILE *file = fopen("Id.txt", "r+");
    if (!file)
    {
	cerr << "UNABLE TO OPEN ID FILE" << endl;
    }
    // Read a string from the file
    for(int i =0; i <= slot; i++)
    {
	fscanf(file,"%[^\n]\n",temp);
    }
    cout << "ID is : " << temp << endl;
    cout << "pss is : " << pass << endl;

    fseek(fptr,slot,SEEK_SET);
    fread(&ch,1,1,fptr);
    if(ch == '1')
    {
	if(strncmp(pass,temp,5) == 0)
	{
	    cout << "-----------------------------------"<< endl;
	    cout << " ID IS MATCHING "<< endl;
	    cout << "-----------------------------------"<< endl;
	    fseek(fptr,slot,SEEK_SET);
	    fputc('0',fptr); 
	    fseek(file,-6,SEEK_CUR);
	    fprintf(file,"%s\n","00000"); 
	    fclose(fptr);
	    fclose(file);
	    display();
	}
	else
	{
	    cout << "-----------------------------------"<< endl;
	    cout << "UNABLE TO EXIT ENTERED ID IS NOT MATCHING"<< endl;
	    cout << "-----------------------------------"<< endl;
	    fclose(fptr);
	    fclose(file);
	}
    }
    else
    {
	cout << "-----------------------------------"<< endl;
	cout << "ENTERED SLOT NUMBER IS WRONG"<< endl;
	cout << "-----------------------------------"<< endl;
	fclose(fptr);
	fclose(file);
    }
}

