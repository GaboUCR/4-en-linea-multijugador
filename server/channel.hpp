#ifndef CHANNEL_H
#define CHANNEL_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <shared_mutex>
#include <iostream>

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

struct channel {
    std::shared_ptr<websocket::stream<tcp::socket>> session;
    std::shared_mutex mutex;
};

void write_to_channel(channel& ch, const std::vector<uint8_t>& data);

#endif // CHANNEL_H
