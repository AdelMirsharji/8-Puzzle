#include <iostream>
#include <vector>
#include <unistd.h>

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
			cout << "State-" << state_number << " baord is:" << endl;

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

State bfs_search(vector<State> &states,int &num_visit, int &num_exp, int &a_bfs_reached_goal) {
	bool result;

	while(!states.empty()){
		State it_state = states.front();
		
		cout << "State getting expanded in BFS = " << endl;
		it_state.print_board();

		cout << endl << "************************" << endl;
		cout << "Number of visited nodes = " << num_visit << "      " << "Number of expanded nodes = " << num_exp << endl;
		cout << endl << "************************" << endl;

		result = check_if_it_is_goal(it_state);
		if (result == true) {
			a_bfs_reached_goal = 1;
			return it_state;
		}

		creating_child(states, it_state, num_visit, num_exp);
		num_exp++;
	}

	return states.back();
}

int main() {
	//***********************************README and MENU
	cout << endl << "**************************************************************" << endl;
	cout << "The program compiled and will run!" << endl;
	cout << "The BFS search will starts in 5s:" << endl;
	cout << "**************************************************************" << endl;
	sleep(5);
	//***********************************End of readme and menu

	int starting_board[9] = { 7,5,blank,1,4,3,6,2,8};
	State first_state(1,2,-10, starting_board);
	vector<State> states;

	cout << "A)BFS search" << endl << endl;
	int a_bfs_number_of_nodes_visited = 0;			//A)BFS visited nodes number
	int a_bfs_number_of_nodes_expanded = 0;			//A)BFS expanded nodes number
	int a_bfs_reached_goal = 0;						//A)checking if it reached goal

	//Initializing A)BFS
	states.push_back(first_state);
	a_bfs_number_of_nodes_visited++;

	State final_a_bfs_state = bfs_search(states, a_bfs_number_of_nodes_visited, a_bfs_number_of_nodes_expanded, a_bfs_reached_goal);
	if (a_bfs_reached_goal == 1)
		cout << "A)BFS search reached the goal!" << endl;
	else
		cout << "A)BFS search didnt reach the goal and terminated!" << endl;

	cout << endl << "Final state in A)BFS search:" << endl;
	final_a_bfs_state.print_board();
	cout << endl << "Number of visited nodes in A)BFS search = " << a_bfs_number_of_nodes_visited << endl << "Number of expanded nodes in A)BFS search = " << a_bfs_number_of_nodes_expanded << endl;

}	