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

int calculate_HX_value(State state){
	int goal[9] = {1,2,3,4,5,6,7,8,-9};
	int HX_value = 0;
	int *state_board = state.get_board();
	for(int i = 0 ; i < 9 ; ++i){
		if(state_board[i] != goal[i])
			HX_value++;
	}
	return HX_value;
}

State A_star_search(vector<State> &states,int &num_visit, int &num_exp, int &f_a_star_reached_goal) {
	bool result;
	vector<State> open_states;
	open_states.push_back(states.front());
	vector<int> FX_values;
	int GX_value = 0;
	int HX_value = 0;
	int FX_value = 0;
	int least_FX = 0;
	int least_FX_state_number;

	while(!open_states.empty()){

		State it_state = open_states.front();
		cout << endl << "State being check" << endl;
		it_state.print_board();
		result = check_if_it_is_goal(it_state);
		if(result == true){
			f_a_star_reached_goal = 1;
			return it_state;
		}

		GX_value++;
		creating_child(open_states,it_state,num_visit,num_exp);
		cout << endl << "*************************" << endl;
		cout << endl << "The child are:" << endl;
		for(int j = 0 ; j < open_states.size() ; ++j){
			open_states[j].print_board();
			HX_value = calculate_HX_value(open_states[j]);
			FX_value = HX_value + GX_value;
			FX_values.push_back(FX_value);
		}
		cout << endl << "*************************" << endl;
		num_exp++;

		least_FX = FX_values[0];
		least_FX_state_number = 0;
		for(int j = 0 ; j < FX_values.size() ; ++j){
			if(least_FX > FX_values[j]){
				least_FX = FX_values[j];
				least_FX_state_number = j;
			}
		}
		cout << endl << "Next state is = " << endl;
		open_states[least_FX_state_number].print_board();
		State next_state_to_traverse = open_states[least_FX_state_number];
		open_states.clear();
		FX_values.clear();
		open_states.push_back(next_state_to_traverse);

		cout << endl << "************************" << endl;
		cout << "Number of visited nodes = " << num_visit << "      " << "Number of expanded nodes = " << num_exp << endl;
		cout << endl << "************************" << endl;
	}
	return states.back();
}

int main() {
	//***********************************README and MENU
	cout << endl << "**************************************************************" << endl;
	cout << "The program compiled and will run!" << endl;
	cout << "The A* search will starts in 5s:" << endl;
	cout << "**************************************************************" << endl;
	sleep(5);
	//***********************************End of readme and menu

	int starting_board[9] = { 7,5,blank,1,4,3,6,2,8};
	State first_state(1,2,-10, starting_board);
	vector<State> states;

	cout << "F)A* search" << endl << endl;
	int f_a_star_number_of_nodes_visited = 0;			//F)A* visited nodes number
	int f_a_star_number_of_nodes_expanded = 0;			//F)A* expanded nodes number
	int f_a_star_reached_goal = 0;						//F)checking if it reached goal

	//Initializing F)A*
	states.push_back(first_state);
	f_a_star_number_of_nodes_visited++;

	auto t1 = std::chrono::high_resolution_clock::now();
	State final_f_a_star_state = A_star_search(states, f_a_star_number_of_nodes_visited, f_a_star_number_of_nodes_expanded, f_a_star_reached_goal);
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

	if (f_a_star_reached_goal == 1){
		cout << "F)A* search reached the goal!" << endl;
		cout << "Time taken by A* search to find the answer is (" << duration << " microseconds)" << endl;
		cout << "Number of visited nodes in F_A* search = " << f_a_star_number_of_nodes_visited << endl;
		cout << "Number of expanded nodes in F_A* search = " << f_a_star_number_of_nodes_expanded << endl;
		cout << endl << "Final state in F_A* search:" << endl;
		final_f_a_star_state.print_board();
	}

	else{
		cout << "F_A* search didnt reach the goal and terminated!" << endl;
		cout << "Number of visited nodes in F_A* search = " << f_a_star_number_of_nodes_visited << endl;
		cout << "Number of expanded nodes in F_A* search = " << f_a_star_number_of_nodes_expanded << endl;
		cout << endl << "Final state in F_A* search:" << endl;
		final_f_a_star_state.print_board();
	}

	return 0;
}	