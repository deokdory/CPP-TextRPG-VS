#include "Quest.h"
#include "pch.h"

CompletedQuest* CompletedQuest::Head = nullptr;
CompletedQuest* CompletedQuest::Tail = nullptr;
int CompletedQuest::Length = 0;

CompletedQuest::CompletedQuest(int _index)
	: completed_quest_index(_index), Next(nullptr) {}

void CompletedQuest::NewCompletedQuest(int _index) {
	CompletedQuest* node = new CompletedQuest(_index);
	node->Push();
}

void CompletedQuest::Push() {
	if (Head == nullptr) {
		Head = this;
		Tail = this;
	}

	else {
		Tail->Next = this;
		Tail = this;
	}

	Length++;
}

bool CompletedQuest::CheckIsCompletedQuest(int _index) {
	if (Head == nullptr) {
		return false;
	}

	CompletedQuest* checker = Head;

	while (true) {
		if (checker->GetCompletedQuestIndex() == _index)
			return true;
		else if (checker->Next != nullptr)
			checker = checker->Next;
		else
			return false;
	}
}

void CompletedQuest::Remove() {
	if (Head == this) {
		if (this->Next != nullptr) {
			Head = this->Next;
		}
		else {
			Head = Tail = nullptr;
		}
	}
	else {
		CompletedQuest* cur = Head;

		while (true) {
			if (cur->Next != nullptr) {
				if (cur->Next == this) {
					cur->Next = this->Next;
					break;
				}
				else { cur = cur->Next; }
			}
			else {
				break;
			}
		}
	}
	delete this;
	Length--;
}


void CompletedQuest::RemoveAll(CompletedQuest* node) {
	Length = 0;

	if (Head == nullptr) {
		std::cout << "CompletedQuestList is null" << std::endl;
		system("pause");
		return;
	}

	if (Head->Next != nullptr) {
		RemoveAll(Head->Next);
	}
	delete this;
}