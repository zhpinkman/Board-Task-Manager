#include <iostream>
#include "interface.hpp"

int main()
{
	Interface interface;
	
	interface.addUser("Zhivar");
	interface.addUser("Amir");
	interface.addUser("Bardia");

	interface.addList("Code");
	interface.addList("Description");
	interface.addList("Misc");

	interface.addTask("Code", "Do Everything", 12, 1, "Write the whole code");
	interface.assignTask("Do Everything", "Bardia");
	interface.addTask("Code", "Destroy code formatting", 1, 2, "Rewrite the whole code in a worse format");
	interface.assignTask("Destroy code formatting", "Zhivar");

	interface.addTask("Description", "Write Description", 3, 1, "Write the damn description");
	interface.assignTask("Write Description", "Amir");
	interface.addTask("Misc", "Upload Assignment", 1, 1, "Upload it");

	interface.completeTask("Do Everything");
	interface.printUsersByPerformance();

	interface.printUnassignedTasksByPriority();
	interface.deleteTask("Upload Assignment");
	interface.printAllUnfinishedTasksByPriority();

	interface.addTask("Misc", "Have fun", 10, 2, "Just do it");
	interface.moveTask("Have fun", "Code");
	interface.printTask("Have fun");

	interface.printList("Code");
	return 0;
}