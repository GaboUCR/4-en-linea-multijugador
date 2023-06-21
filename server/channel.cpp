#include "channel.hpp"

void write_to_channel(channel& ch, const std::vector<uint8_t>& data)
{
    std::unique_lock lock(ch.mutex);
    auto buffer = boost::asio::buffer(data);
    boost::system::error_code ec;
    ch.session->write(buffer, ec);

    if(ec)
    {
        // handle the error
        std::cerr << "write_to_channel error: " << ec.message() << std::endl;
    }
}
