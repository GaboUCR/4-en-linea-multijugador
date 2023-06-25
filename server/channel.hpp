#ifndef CHANNEL_H
#define CHANNEL_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <shared_mutex>
#include <iostream>
#include <vector>

using tcp = boost::asio::ip::tcp; // Usando alias para simplificar la notación de tcp
namespace websocket = boost::beast::websocket; // Usando alias para simplificar la notación de websocket

/**
 * @brief Estructura que representa un canal de comunicación.
 * 
 * Un canal incluye un socket de websocket compartido y un mutex para sincronizar el acceso a la sesión.
 */
struct channel {
    std::shared_ptr<websocket::stream<tcp::socket>> session; ///< Puntero compartido a la sesión de websocket.
    std::shared_mutex mutex; ///< Mutex para sincronizar el acceso a la sesión.
};

/**
 * @brief Escribe datos en un canal específico.
 * 
 * Esta función toma una referencia a un canal y un vector de bytes como datos,
 * y escribe los datos en el canal.
 *
 * @param ch Referencia al canal en el cual se escribirán los datos.
 * @param data Vector de bytes que contiene los datos a ser escritos.
 */
void write_to_channel(channel& ch, const std::vector<uint8_t>& data);

#endif // CHANNEL_H
