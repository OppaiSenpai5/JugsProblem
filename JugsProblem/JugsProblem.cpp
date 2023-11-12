#include "JugsProblem.h"

#include <iostream>
#include <vector>
#include <algorithm>

JugsProblem::JugsProblem(liters x, liters y, liters z, liters v)
	: max_capacity{ x, y, z },
	val(v),
	states(),
	unique_states()
{
	unique_states.insert({ EMPTY_STATE, EMPTY_STATE });
	states.push(EMPTY_STATE);
}

void JugsProblem::solve()
{
	auto result = search_for_val();
	print_steps_to(result);
}

JugsProblem::state JugsProblem::search_for_val()
{
	while (!states.empty())
	{
		auto old_state = states.front();
		states.pop();

		for (size_t i = 0; i < old_state.size(); i++)
		{
			auto new_state = drain(old_state, i);
			add_new_entry(new_state, old_state);
			if (found_val(new_state))
			{
				return new_state;
			}

			new_state = fill(old_state, i);
			add_new_entry(new_state, old_state);
			if (found_val(new_state))
			{
				return new_state;
			}

			for (size_t j = 0; j < old_state.size(); j++)
			{
				new_state = pour(old_state, i, j);
				add_new_entry(new_state, old_state);
				if (found_val(new_state))
				{
					return new_state;
				}
			}
		}
	}

	return EMPTY_STATE;
}

void JugsProblem::add_new_entry(const state& new_state, const state& old_state)
{
	if (!unique_states.count(new_state))
	{
		unique_states.insert({ new_state, old_state });
		states.push(new_state);
	}
}

bool JugsProblem::found_val(const state& st)
{
	return std::find(st.cbegin(), st.cend(), val) != st.cend();
}

JugsProblem::state JugsProblem::fill(state st, size_t i)
{
	st[i] = max_capacity[i];
	return st;
}

JugsProblem::state JugsProblem::drain(state st, size_t i)
{
	st[i] = 0;
	return st;
}

JugsProblem::state JugsProblem::pour(state st, size_t i, size_t j)
{
	auto poured = std::min(st[i], max_capacity[j] - st[j]);
	st[i] -= poured;
	st[j] += poured;
	return st;
}

void JugsProblem::print_state(const state& st)
{
	std::cout << '(';

	state::const_iterator begin = st.cbegin(), end = st.cend();
	for (auto it = begin; it != end; ++it)
	{
		if (it != begin)
		{
			std::cout << ", ";
		}
		std::cout << *it;
	}

	std::cout << ')';
}

void JugsProblem::print_steps_to(const state& answer)
{
	if (answer != EMPTY_STATE)
	{
		std::vector<state> steps{ answer };

		while (steps.back() != EMPTY_STATE)
		{
			steps.push_back(unique_states[steps.back()]);
		}

		std::cout << "A volume of " << val
			<< " liters can be achieved in "
			<< steps.size() - 1 << " steps."
			<< std::endl;

		decltype(steps)::const_reverse_iterator
			begin = steps.crbegin(),
			end = steps.crend();
		for (auto it = begin; it != end; ++it)
		{
			if (it != begin)
			{
				std::cout << " -> ";
			}
			print_state(*it);
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "A volume of " << val
			<< " liters is unachieveable!"
			<< std::endl;
	}
}
