#pragma once

#include <cstdlib>
#include <queue>
#include <array>
#include <map>

class JugsProblem
{
public:
	static constexpr std::size_t NUM_OF_JUGS = 3;

	using liters = std::size_t;
	using state = std::array<liters, NUM_OF_JUGS>;

	static constexpr state EMPTY_STATE = { 0, 0, 0 };

	JugsProblem(liters x, liters y, liters z, liters v);

	void solve();

private:
	state max_capacity;
	liters val;
	std::queue<state> states;
	std::map<state, state> unique_states;

	state search_for_val();
	void add_new_entry(const state& new_state, const state& old_state);
	bool found_val(const state& st);
	state fill(state st, size_t i);
	state drain(state st, size_t i);
	state pour(state st, size_t i, size_t j);
	void print_state(const state& st);
	void print_steps_to(const state& answer);
};