#ifndef __SERVICE_CLIENT_HPP__
#define __SERVICE_CLIENT_HPP__

#include <rclcpp/rclcpp.hpp>
#include <ariac_msgs/msg/competition_state.hpp>
#include <std_srvs/srv/trigger.hpp>

class ServiceClientNode : public rclcpp::Node {
    
    public:
     
     // default ctor
     ServiceClientNode() : Node("service_client_node"){

        // client 
        m_competition_start_client = this->create_client<std_srvs::srv::Trigger>("/ariac/start_competition");

        // subscriber callback
        m_competition_state_subscriber = this->create_subscription<ariac_msgs::msg::CompetitionState>("ariac/competition_state", 10, 
                                                std::bind(&ServiceClientNode::competition_state_subscriber_callback,
                                                                                        this, std::placeholders::_1));

     }

    private:
     // attributes

     /**
      * @brief Shared pointer to create_subscription object
      * 
      */
     rclcpp::Subscription<ariac_msgs::msg::CompetitionState>::SharedPtr m_competition_state_subscriber;

     /**
      * @brief Keep track of competition state
      * 
      */
     bool m_competition_state;

     rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr m_competition_start_client;


     // methods

     /**
      * @brief Subscriber to competition state
      * 
      * @param msg Shared pointer to msg object
      */
     void competition_state_subscriber_callback(ariac_msgs::msg::CompetitionState::SharedPtr msg);

     /**
      * @brief Call the competition service
      * 
      */
     void call_competition_service();

     /**
      * @brief Callback function for the client
      * 
      * This function is called when the client receives a response from the server
      * @param future Shared pointer to the future object.
      * A future is a value that indicates whether the call and response is finished (not the value of the response itself)
      */
     void response_callback(rclcpp::Client<std_srvs::srv::Trigger>::SharedFuture future);

}; // class ServiceClientNode 

#endif