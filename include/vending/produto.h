#pragma once // Impede o compilador de ler este ficheiro duas vezes, evitando erros.

#include <string>  // Inclui as ferramentas para usar texto (std::string).
#include <cstdint> // Inclui os inteiros com tamanho fixo garantido (std::int64_t).

namespace vending { // 📂 Cria a "gaveta" (namespace) para organizar o código do projeto.

    // ALIAS: Cria o apelido "Centimos". Substitui o detalhe técnico por significado de negócio.
    using Centimos = std::int64_t;

    // ENUM CLASS: Catálogo fechado de erros lógicos. Nenhum = 0 é o sinal de "sucesso".
    enum class ErroCriacaoProduto {
    Nenhum = 0,          // success
    IdInvalido,          // REQ-003
    NomeInvalido,        // REQ-004
    PrecoInvalido,       // REQ-005
    VolumeInvalido,      // REQ-006 (Bebida)
    CaloriasInvalidas    // REQ-007 (Snack)
};

    // CLASSE ABSTRATA: Serve apenas de molde. Não se podem criar objetos diretamente dela.
    class Produto {
    public:

        // DESTRUTOR VIRTUAL: Caixote do lixo do objeto. 
        // OBRIGATÓRIO ser virtual para que o C++ limpe as classes filhas (Bebida/Snack) sem deixar lixo na memória.
        virtual ~Produto() = default;

        // MÉTODO VIRTUAL PURO: O "= 0" diz que a mãe não sabe o código, obrigando as filhas a programá-lo.
        // O "const" garante que quem chamar esta função não vai alterar os dados do produto.
        virtual std::string descricao() const = 0;

        // GETTER (Nome): Outro método de LEITURA para obter o nome com segurança de fora da classe.
        const std::string& getNome() const;

        // GETTER (Preço): Método público de LEITURA. Permite saber o preço sem aceder à variável direta.
        // O "const" no fim tranca a função, impedindo-a de modificar o objeto (garante a imutabilidade).
        Centimos getPreco() const;
        const std::string& getId() const;         // 🌟 JUNTADO ID: Número pequeno -> por valor [1]

        // NOTA: NÃO HÁ SETTERS AQUI! Retirar os métodos de alteração (setters) é o que torna o produto imutável.

    protected: // 👥 ACESSO PROTEGIDO: Só esta classe e as suas subclasses (Bebida/Snack) podem mexer.

        // CONSTRUTOR PROTEGIDO: O código de fora da máquina não pode fazer "new Produto".
        // Só as classes filhas o podem invocar quando nascem.
        Produto(std::string id, std::string nome, Centimos preco);

        // 🌟 CORREÇÃO DO VALIDARCOMUM: 
        // 1. Agora recebe o id como primeiro parâmetro.
        // 2. Devolve o tipo "Erro" em vez de void.
        // 3. Tem o [[nodiscard]] para o compilador dar erro se alguém ignorar o resultado.
        [[nodiscard]] static ErroCriacaoProduto validarComum(const std::string& id, const std::string& nome, Centimos preco);
    private: // 🔒 ACESSO PRIVADO: Totalmente trancado. Só a própria classe Produto lê ou escreve aqui.
        
        // ATRIBUTOS PRIVADOS: Onde os dados reais ficam guardados a sete chaves.
        // O underscore "_" no fim cumpre rigorosamente as regras de estilo do teu clang-tidy.
        std::string id_; // 🌟 JUNTADO ID NOS ATRIBUTOS
        std::string nome_;
        Centimos preco_;
    };

} // Fim do namespace vending