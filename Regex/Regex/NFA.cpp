#include "NFA.h"

namespace anyun_regex
{
#define VISITED_ONE_NODE(visit_node_id,the_queue,the_states)\
	do {										\
		if(visited[visit_node_id] == false)		\
		{										\
			visited[visit_node_id] = true;		\
			the_queue.push(visit_node_id);		\
			the_states.insert(visit_node_id);}	\
	} while (0)



	NFA::NFA(const char * pattern)
		: digraph(new DirectedGraph(pattern))
	{

	}

	NFA::NFA(const string & pattern)
		: digraph(new DirectedGraph(pattern))
	{
	}

	NFA::~NFA()
	{
	}

	bool NFA::compile(const string & pattern)
	{
		digraph.reset(new DirectedGraph(pattern));
		return digraph->parse_result == REGEX_PARSE_OK;
	}

	RegexParseCode NFA::get_compile_result_code() const
	{
		return digraph->parse_result;
	}

	string NFA::get_compile_message() const
	{
		return PARSE_RESULT_MESSAGE[digraph->parse_result];
	}


	string NFA::get_pattern() const
	{
		return digraph->pattern;
	}

	size_t NFA::group_size() const
	{
		return digraph->groups.size();
	}

	size_t NFA::node_size() const
	{
		return digraph->nodes.size();
	}

	size_t NFA::edge_size() const
	{
		return digraph->edges.size();
	}


	size_t NFA::update_group_node_record(TrackRecord& record, Matcher & matcher) const
	{

		vector<Group> &groups = digraph->groups;
		size_t groups_size = groups.size();
		for (size_t i = 0; i < groups_size; i++)
		{
			size_t group_start_node_id = groups[i].group_start_node;
			size_t group_end_node_id = groups[i].group_end_node;
			matcher.groups[i].first = record[group_start_node_id].first;
			matcher.groups[i].second = record[group_end_node_id].first;
		}
		return matcher.groups[0].second;
	}

	void NFA::get_next_state(SaveState & state, const string & text, Matcher & matcher) const
	{
		/*
		 *
		 *important here need some code for push one group in group-stack
		 *	don't add group name to map like before
		 *push group name and capture in stack when match
		 *
		 */



		//get the neccessary information
		OneSaveState &one_save_state = state.top();	 //the top state
		size_t &top_node_id = std::get<0>(one_save_state);
		size_t &next_edge_id = std::get<1>(one_save_state);
		TrackRecord &track_recode = std::get<2>(one_save_state);
		size_t top_node_cursor_posotion = track_recode[top_node_id].first;
		//all edges
		vector<DirectedEdgePoint> &edges = digraph->edges;
		// the out edges of top node
		const vector<size_t> &out_edges = digraph->nodes[top_node_id]->get_out_edges();
		if (next_edge_id >= out_edges.size())
			state.pop();
		else if (digraph->nodes[top_node_id]->get_type() == REPEAT_COUNT_DIRECTEDNODE)//especaillly case for repeatcount
		{
			RepeatCountDirectedNode &repeat_node = *dynamic_cast<RepeatCountDirectedNode *>(digraph->nodes[top_node_id].get());
			// add one to the repeat times
			size_t &repeat_times = track_recode[top_node_id].second;
			int judge = repeat_node.accept_count(repeat_times);
			/*
			-1 <
			0 range
			1 upper range
			2 beyond
			*/
#define UPDATE_STATE(the_one_state,update_index,current_cursor_position) \
					do {\
						size_t to_edge_id = repeat_node.get_out_edges()[update_index];\
						size_t &the_top_node_id = std::get<0>(the_one_state);	\
						size_t &the_next_edge_id = std::get<1>(the_one_state);	\
						TrackRecord &top_track_recode = std::get<2>(the_one_state); \
						the_top_node_id = digraph->edges[to_edge_id]->get_end_node_id(); \
						the_next_edge_id = 0;		\
						top_track_recode[the_top_node_id].first = current_cursor_position;\
						top_track_recode[the_top_node_id].second++;\
					}while(0)

#define SET_CONTINUE_REPEAT(the_one_state,current_cursor_position)	UPDATE_STATE(the_one_state,0,current_cursor_position);
#define SET_PASS_STATE(the_one_state,current_cursor_position)		UPDATE_STATE(the_one_state,1,current_cursor_position);
#define ADD_NEW_STATE\
					do {\
						OneSaveState &the_top_state = state.top();	 \
						size_t &the_top_node_id = std::get<0>(the_top_state);	\
						size_t &the_next_edge_id = std::get<1>(the_top_state);	\
						TrackRecord &top_track_recode = std::get<2>(the_top_state); \
						state.push({ the_top_node_id,the_next_edge_id,top_track_recode });\
					}while(0)
			switch (judge)
			{
			case -1:
				{
					//the continue repeat node
					SET_CONTINUE_REPEAT(one_save_state, top_node_cursor_posotion);
					break;
				}
			case 0:
				{
					
					ADD_NEW_STATE;
					//judge lazy match
					if(repeat_node.is_lazy())
					{
						SET_CONTINUE_REPEAT(one_save_state, top_node_cursor_posotion);
						OneSaveState &pass_state = state.top();
						SET_PASS_STATE(pass_state, top_node_cursor_posotion);
					}
					else
					{
						SET_PASS_STATE(one_save_state, top_node_cursor_posotion);
						OneSaveState &continue_repeat_state = state.top();
						SET_CONTINUE_REPEAT(continue_repeat_state, top_node_cursor_posotion);
					}
					break;
				}
			case 1:
				{
					SET_PASS_STATE(one_save_state, top_node_cursor_posotion);
					break;
				}
			default:
				state.pop();
			}

		}
		else
		{
			/*
			 *judge the edge can accept the str?
			 *if accept:
			 *	 next_edge_id++;
			 *	 push a new OneSaveState;
			 *	 the sate should update its information
			 *else
			 *	 next_edge_id++;
			 */
			size_t step = static_cast<unsigned>(-1);	//the step of the str_point should go if the edge accept it
			DirectedEdgePoint current_edge = edges[out_edges[next_edge_id]];
			if ((step = current_edge->accept(text, track_recode[top_node_id].first , matcher, track_recode)) != static_cast<unsigned>(-1))
			{
				/*
				 * 	 push a new OneSaveState;
				 *	 the sate should update its information
				 */
				size_t end_node_id = current_edge->get_end_node_id();		//the end node id
				//update new TrackRecord
				TrackRecord new_state_record = track_recode;
				new_state_record[end_node_id] = { new_state_record[top_node_id].first + step , new_state_record[end_node_id].second + 1 };
				state.push({ end_node_id,0,new_state_record });
			}
			next_edge_id++;
		}
	}

}
