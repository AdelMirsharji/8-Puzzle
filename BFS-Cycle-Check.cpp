#include <iostream>
#include <vector>
#include <unistd.h>
#include<bits/stdc++.h>

using namespace std;

constexpr int blank = -9;

class State {
	private:
		int state_number;
		int blank_location;
		int pervious_parent_blank_location;
		int board[9];
		
	public:
		int get_state_number() { return this->state_number; };
		int get_blank() { return this->blank_location; }
		int get_pervious_blank() { return this->pervious_parent_blank_location; };
		int *get_board() { return this->board; }
		void print_board() {
			cout << "State-" << state_number << " board is:" << endl;
			cout << endl<< "   " << board[0] << ", " << board[1] << ", " << board[2] << endl
				 << "   " << board[3] << ", " << board[4] << ", " << board[5] << endl
				 << "   " << board[6] << ", " << board[7] << ", " << board[8] << endl;
		}

		State(int state_number, int blank_location,int pervious_parent_blank_location, int *board) {

			this->state_number = state_number;
			this->blank_location = blank_location;
			this->pervious_parent_blank_location = pervious_parent_blank_location;
			for (int i = 0; i < 9; ++i)
				this->board[i] = board[i];
		}

};

bool check_if_it_is_goal(State state) {
	int *board_of_this_state = state.get_board();
	for (int i = 0; i < 9; ++i) {
		if (i != 8) {
			if (board_of_this_state[i] != i + 1)
				return false;
		}
	}
	return true;
}

void creating_child(vector<State> &states, State state, int &num_vis, int &num_exp) {
	states.erase(states.begin());
	int pervious_blank_location = state.get_pervious_blank();
	int blank_location = state.get_blank();
	int *it_board = state.get_board();

	int new_pervious_blank_location = 0;
	int new_blank_location = 0;
	int new_board[9];

	if ((blank_location - 3) >= 0 && (blank_location - 3) != pervious_blank_location) {			//checking upper tile if it is possible to move to
		num_vis++;
		new_pervious_blank_location = blank_location;
		new_blank_location = (blank_location - 3);
		for (int i = 0; i < 9; ++i) {
			if (i == new_blank_location) {
				new_board[i] = blank;
				new_board[blank_location] = it_board[i];
			}
			else if(i != new_blank_location && i != blank_location)
				new_board[i] = it_board[i];
		}
		State s(num_vis, new_blank_location, new_pervious_blank_location, new_board);
		states.push_back(s);
	}
	if ((blank_location - 1) >= 0 && (blank_location - 1) != 2 && (blank_location - 1) != 5 && (blank_location - 1) != pervious_blank_location){		//checking left tile if it is possible to move to
		num_vis++;
		new_blank_location = (blank_location - 1);
		for (int i = 0; i < 9; ++i) {
			if (i == new_blank_location) {
				new_board[i] = blank;
				new_board[blank_location] = it_board[i];
			}
			else if (i != new_blank_location && i != blank_location)
				new_board[i] = it_board[i];
		}
		State s(num_vis, new_blank_location, new_pervious_blank_location, new_board);
		states.push_back(s);
	}
	if ((blank_location + 3) <= 8 && (blank_location + 3) != pervious_blank_location) {			//checking bottom tile if it is possible to move to
		num_vis++;
		new_blank_location = (blank_location + 3);
		for (int i = 0; i < 9; ++i) {
			if (i == new_blank_location) {
				new_board[i] = blank;
				new_board[blank_location] = it_board[i];
			}
			else if (i != new_blank_location && i != blank_location)
				new_board[i] = it_board[i];
		}
		State s(num_vis, new_blank_location, new_pervious_blank_location, new_board);
		states.push_back(s);
	}
	if ((blank_location + 1) <= 8 && (blank_location + 1) != 3 && (blank_location + 1) != 6 && (blank_location + 1) != pervious_blank_location) {		//checking right tile if it is possible to move to
		num_vis++;
		new_blank_location = (blank_location + 1);
		for (int i = 0; i < 9; ++i) {
			if (i == new_blank_location) {
				new_board[i] = blank;
				new_board[blank_location] = it_board[i];
			}
			else if (i != new_blank_location && i != blank_location)
				new_board[i] = it_board[i];
		}
		State s(num_vis, new_blank_location, new_pervious_blank_location, new_board);
		states.push_back(s);
	}
}

State bfs_search(vector<State> &states,int &num_visit, int &num_exp, int &c_bfs_cc_reached_goal) {
	bool result;
	vector<State> checked_states;
	int number_of_same_tile;
	int state_is_checked_before;
	int *board;
	int *temp_state_board;

	while(!states.empty()){
		int state_is_checked_before = 0;
		State it_state = states.front();
		board = it_state.get_board();

		for(int i = 0 ; i < checked_states.size() ; ++i){
			number_of_same_tile = 0;
			temp_state_board = checked_states[i].get_board();
			for(int j = 0 ; j < 9 ; ++j){
				if(board[j] == temp_state_board[j]){
					number_of_same_tile++;
				}
			}
			if(number_of_same_tile == 9){
				cout << endl << endl << "**************************************************" << endl;
				cout << "Skiped state cause of Cycle-check is:" << endl;
				it_state.print_board();
				cout << "Same whit alreadys state = " << endl; 
				checked_states[i].print_board();
				cout << endl << "**************************************************" << endl << endl;
				state_is_checked_before = 1;
				break;
			}
		}

		if(state_is_checked_before == 1){
			states.erase(states.begin());
			continue;
		}
		
		cout << "State getting expaned in BFS whit ((cycle check)): " << endl;
		it_state.print_board();

		result = check_if_it_is_goal(it_state);
		if (result == true) {
			c_bfs_cc_reached_goal = 1;
			return it_state;
		}

		creating_child(states, it_state, num_visit, num_exp);
		checked_states.push_back(it_state);
		num_exp++;
	}

	return states.back();
}

int main() {
	//***********************************README and MENU
	cout << endl << "**************************************************************" << endl;
	cout << "The program compiled and will run!" << endl;
	cout << "BFS search whit Cycle-check found an answer for 8-puzzle given in question in (6.437385917 min) = (386243155 microsecnods) in a system whit below configuration:" << endl;
	cout << "System configuration:" << endl;
	cout << "1-Memory: 7.5Gib" << endl;
	cout <<	"2-Processor: Intel(R) Core(TM) i5-3230M CPU @2.60Ghz x 4" << endl;
	cout <<	"3-Graphics: Intel(R) HD Graphics 4000(IVB GT2)" << endl;
	cout <<	"4-Operating system: Ubuntu 20.04.1 LTS" << endl;
	cout <<	"5-OS-type: 64-bit" << endl;
	cout << "6-Written in C++" << endl;

	cout << endl << "BFS whit Cycle-check search will start in 40s!" << endl;
	cout << "**************************************************************" << endl;
	sleep(40);
	//***********************************End of readme and menu

	int starting_board[9] = { 7,5,blank,1,4,3,6,2,8};
	State first_state(1,2,-10, starting_board);
	vector<State> states;

	cout << "C)BFS whit Cycle-check search" << endl << endl;
	int c_bfs_number_of_nodes_visited = 0;			//C)BFS whit Cycle-check visited nodes number
	int c_bfs_number_of_nodes_expanded = 0;			//C)BFS whit Cycle-check nodes number
	int c_bfs_reached_goal = 0;						//C)checking if it reached goal

	//Initializing C)BFS whit Cycle-check
	states.push_back(first_state);
	c_bfs_number_of_nodes_visited++;

	auto t1 = std::chrono::high_resolution_clock::now();
	State final_c_bfs_state = bfs_search(states, c_bfs_number_of_nodes_visited, c_bfs_number_of_nodes_expanded, c_bfs_reached_goal);
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

	if (c_bfs_reached_goal == 1){
		cout << endl << endl << "-----------------------------------------------------------------------" << endl;
		cout << endl << "C)BFS whit Cycle-check search reached the goal!" << endl;
		cout << "Time taken to find answer using BFS whit (Cycle-check) is = " << duration << " microsecnods" << endl;
		cout << endl << "Number of visited nodes in C)BFS whit Cycle-check search = " << c_bfs_number_of_nodes_visited << endl;
		cout << endl << "Number of expanded nodes in C)BFS whit Cycle-check search = " << c_bfs_number_of_nodes_expanded << endl;
		cout << endl << "Final state in C)BFS whit Cycle-check search:" << endl;
		final_c_bfs_state.print_board();
		cout << endl << endl << "-----------------------------------------------------------------------" << endl;
	}

	else{
		cout << endl << endl << "-----------------------------------------------------------------------" << endl;
		cout << endl << "C)BFS whit Cycle-check search didnt reach the goal and terminated!" << endl;
		cout << endl << "Number of visited nodes in C)BFS whit Cycle-check search = " << c_bfs_number_of_nodes_visited << endl;
		cout << endl << "Number of expanded nodes in C)BFS whit Cycle-check search = " << c_bfs_number_of_nodes_expanded << endl;
		cout << endl << "Final state in C)BFS whit Cycle-check search:" << endl;
		final_c_bfs_state.print_board();
		cout << endl << "-----------------------------------------------------------------------" << endl;
	}
}