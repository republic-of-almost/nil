#include <nil/node_event.hpp>
#include <graph/graph_data.hpp>


namespace Nil {
namespace Event {


bool
node_added(const Node_event &evt)
{
  return !!(evt.events & Graph::Event::ADDED);
}


bool
node_moved(const Node_event &evt)
{
  return !!(evt.events & Graph::Event::MOVED);
}


bool
node_removed(const Node_event &evt)
{
  return !!(evt.events & Graph::Event::REMOVED);
}


bool
node_updated(const Node_event &evt)
{
  return !!(evt.events & Graph::Event::UPDATED_DATA);
}


} // ns
} // ns
