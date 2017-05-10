#ifndef NODE_EVENT_INCLUDED_B745B084_85D4_4A3E_9CD0_A81EFF9C7C60
#define NODE_EVENT_INCLUDED_B745B084_85D4_4A3E_9CD0_A81EFF9C7C60


#include <nil/node.hpp>
#include <stdint.h>


namespace Nil {


struct Node_event
{
  Node      node;
  uint32_t  events;
};


namespace Event {


/*!
  Returns true if this node has been added to the graph
*/
bool
node_added(const Node_event &evt);


/*!
  Returns true if this node was moved in the graph.
*/
bool
node_moved(const Node_event &evt);


/*!
  Returns true if this node has been remvoed from the graph.
*/
bool
node_removed(const Node_event &evt);


/*!
  Returns true if this node's data has been updated.
*/
bool
node_updated(const Node_event &evt);


} // ns
} // ns


#endif // inc guard
