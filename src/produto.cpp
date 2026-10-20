#include "vending/produto.h"
#include <utility>

namespace vending {

    // 1. O CONSTRUTOR: Com lista de inicialização e std::move
    Produto::Produto(std::string id, std::string nome, Centimos preco)
        : id_(std::move (id)), 
          nome_(std::move(nome)), 
          preco_(preco) 
    {
        // O corpo do construtor fica vazio porque a inicialização já foi feita acima!
    }

    // 2. OS TRÊS GETTERS: Cada um é apenas um return direto

    const std::string& Produto::getId() const {
        return id_; // Devolve por valor (número pequeno, 8 bytes).
    }

    const std::string& Produto::getNome() const {
        return nome_; // Devolve por const& (janela de leitura para objeto grande).
    }

    Centimos Produto::getPreco() const {
        return preco_; // Devolve por valor (número pequeno, 8 bytes).
    }

} // namespace vending
