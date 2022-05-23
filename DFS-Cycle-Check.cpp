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

State iterative_deepning_dfs_search(vector<State> &states,int &num_visit, int &num_exp, int &d_iddfs_reached_goal) {
	bool result;
	vector<State> expanded_states;
	int it_is_expanded_before;
	int nodes_to_check_to_expand_in_this_depth;

	while(!states.empty()){
		for(int i = 0 ; i < states.size() ; ++i){
			State it_state = states[i];
			result = check_if_it_is_goal(it_state);
			if (result == true) {
				d_iddfs_reached_goal = 1;
				return it_state;
			}
			cout << endl << "State-" << it_state.get_state_number() << " Checked!" << endl;
		}

		cout << endl << "************************" << endl;
		cout << "Number of visited nodes = " << num_visit << "      " << "Number of expanded nodes = " << num_exp << endl;
		cout << endl << "************************" << endl;
		nodes_to_check_to_expand_in_this_depth = states.size();
		cout << endl << "number of nodes to be checked to be expanded or not = " << nodes_to_check_to_expand_in_this_depth << endl;

		for(int i = 0 ; i < nodes_to_check_to_expand_in_this_depth ; ++i){
			it_is_expanded_before = 0;
			for(int j = 0 ; j < expanded_states.size() ; ++j){
				if(states[i].get_state_number() == expanded_states[j].get_state_number())
					it_is_expanded_before = 1;
			}

			if(it_is_expanded_before != 1){
				cout << "State getting expanded in iterative deepening DFS = " << endl;
				states[i].print_board();
				creating_child(states, states[i], num_visit, num_exp);
				num_exp++;
				expanded_states.push_back(states[i]);
			}
		}
	}
	return states.back();
}

int main() {
	//***********************************README and MENU
	cout << endl << "**************************************************************" << endl;
	cout << "Program compiled and will run!" << endl;
	cout << "IDDFS search will starts in 5s:" << endl;
	cout << "**************************************************************" << endl;
	sleep(5);
	//***********************************End of readme and menu

	int starting_board[9] = { 7,5,blank,1,4,3,6,2,8};
	State first_state(1,2,-10, starting_board);
	vector<State> states;

	cout << "D)IDDFS search" << endl << endl;
	int d_iddfs_number_of_nodes_visited = 0;			//D)IDDFS visited nodes number
	int d_iddfs_number_of_nodes_expanded = 0;			//D)IDDFS expanded nodes number
	int d_iddfs_reached_goal = 0;						//D)checking if it reached goal

	//Initializing D)DFS whit Cycle-check
	states.push_back(first_state);
	d_iddfs_number_of_nodes_visited++;

	State final_d_iddfs_state = iterative_deepning_dfs_search(states, d_iddfs_number_of_nodes_visited, d_iddfs_number_of_nodes_expanded, d_iddfs_reached_goal);
	if (d_iddfs_reached_goal == 1)
		cout << "B)IDDFS search reached the goal!" << endl;
	else
		cout << "B)IDDFS search didnt reach the goal and terminated!" << endl;

	cout << endl << "Final state in D)IDDFS search:" << endl;
	final_d_iddfs_state.print_board();
	cout << endl << "Number of visited nodes in D)IDDFS search = " << d_iddfs_number_of_nodes_visited << endl << "Number of expanded nodes in D)IDDFS search = " << d_iddfs_number_of_nodes_expanded << endl;

}	