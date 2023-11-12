#include <cstdlib>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <array>
#include <iostream>
#include <map>

using state = std::array<std::size_t, 3>;

class JugProblem
{
public:
	static constexpr state EMPTY_STATE = { 0, 0, 0 };

	JugProblem(size_t x, size_t y, size_t z, size_t v)
		: max_capacity{x, y, z},
		val(v),
		states(),
		unique_states()
	{
		unique_states.insert({ EMPTY_STATE, EMPTY_STATE });
		states.push(EMPTY_STATE);
	}

	void solve()
	{
		auto result = search();

		if (result != EMPTY_STATE)
		{
			std::vector<state> steps{ result };

			while (steps.back() != EMPTY_STATE)
			{
				steps.push_back(unique_states[steps.back()]);
			}

			std::cout << "v=" << val << " can be achieved in "
				<< steps.size() << " steps" << std::endl;
			for (auto it = steps.crbegin(); it != steps.crend(); it++)
			{
				if (it != steps.crbegin())
				{
					std::cout << " -> ";
				}
				print_state(*it);
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "v=" << val << " is unachieveable!" << std::endl;
		}
	}

private:
	state max_capacity;
	size_t val;
	std::queue<state> states;
	std::map<state, state> unique_states;

	state search()
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

	void add_new_entry(const state& new_state, const state& old_state)
	{
		if (!unique_states.count(new_state))
		{
			unique_states.insert({ new_state, old_state });
			states.push(new_state);
		}
	}

	bool found_val(const state& st)
	{
		return std::find(st.cbegin(), st.cend(), val) != st.cend();
	}

	state fill(state st, size_t i)
	{
		st[i] = max_capacity[i];
		return st;
	}

	state drain(state st, size_t i)
	{
		st[i] = 0;
		return st;
	}

	state pour(state st, size_t i, size_t j)
	{
		auto poured = std::min(st[i], max_capacity[j] - st[j]);
		st[i] -= poured;
		st[j] += poured;
		return st;
	}

	void print_state(const state& st)
	{
		std::cout << '(' << st[0] << ", "
			<< st[1] << ", " << st[2] << ')';
	}
};

int main()
{
	size_t x, y, z, v;

	std::cout << "x=";
	std::cin >> x;
	std::cout << "y=";
	std::cin >> y;
	std::cout << "z=";
	std::cin >> z;
	std::cout << "v=";
	std::cin >> v;

	JugProblem jug_problem(x, y, z, v);
	jug_problem.solve();

	return EXIT_SUCCESS;
}