#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include<string.h>
class ListItem {
	public:
		char* line;
		class ListItem* next;

		ListItem(){}
		ListItem(char* arr){
			int n = strlen(arr)+1;
			int i = 0;
			line = (char*)malloc(n*sizeof(char));
			for (i = 0; i < strlen(arr); i++)
			{
				line[i] = arr[i];
			}
			line[i] = '\0';
			//memcpy(line, arr, strlen(arr)+1);
			next = nullptr;
		}

		void addNext(char* arr)
		{
			next = new ListItem(arr);
			
		}

		~ListItem()
		{
			delete line;
			if (next != nullptr) {
				delete next;
			}
		}
};

class ListContain {
	public:
		ListItem* head;
		ListItem* tail;

		ListContain(char* arr) {
			head = new ListItem(arr);
			tail = new ListItem(arr);
		}
		//add new item for container
		void addList(char* arr) {
			if (head->next == nullptr){
				tail->addNext(arr);
				tail = tail->next;
				head->next = tail;
			}
			else {
				tail->addNext(arr);
				tail = tail->next;
			}
		}

		void print(){
			ListItem* tmp = head;
			while (tmp->next != nullptr) {
				printf("%s\n", tmp->line);
				tmp = tmp->next;
			}
		}

		~ListContain(){
		}
};

int main(int argc, char *argv[])
{
	
	char buffer[1000] = "";
	gets(buffer);
	ListContain list(buffer);
	while (buffer[0] != '.')
	{
		gets(buffer);
		list.addList(buffer);
	}
	list.print();
	getchar();
	return 0;
}
