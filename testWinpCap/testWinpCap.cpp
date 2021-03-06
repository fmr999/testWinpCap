// testWinpCap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <pcap.h>
#include <thread>


using namespace std;
int sharedNum = 0;

int count()
{
	while (true)
	{
		sharedNum=++sharedNum;
		cout << sharedNum + "\n";
	}

}


int main()
{
	// test to do some threading
	std::thread first(count);
	

	first.join();


	pcap_if_t * allAdapters; //a pointer to a string giving a name for the device to pass to pcap_open_live() 
	pcap_if_t * adapter;
	char errorBuffer[PCAP_ERRBUF_SIZE];
	int i = 0; // flag that will check if winPcap is installed

	/* Retrieve the device list from the local machine */
	if (pcap_findalldevs_ex((char*)PCAP_SRC_IF_STRING, NULL, &allAdapters, errorBuffer) == -1)
	{
		fprintf(stderr,"Error in pcap_findalldevs_ex: %s \n",errorBuffer);
		exit(1); //If this is 0 or EXIT_SUCCESS, it indicates success.
	}

	// print the list
	for (adapter = allAdapters; adapter != NULL; adapter = adapter->next)
	{
		printf("%d. %s", ++i, adapter->name);
		if (adapter->description)
			printf(" (%s)\n", adapter->description);
		else
			printf(" (No description available)\n");
	}

	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		//return;
	}



	/* We don't need any more the device list. Free it */
	pcap_freealldevs(allAdapters);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
