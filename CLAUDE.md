# Contexto do projeto (para o Claude)

## Objetivo
Projeto de aprendizagem de C++ moderno do Frederico, para se preparar para uma vaga de
desenvolvimento C++ na Critical FlyTech (Airbus + Critical Software, software safety-critical
para aviação). A vaga valoriza: C++ moderno em produção, CMake, Git, CI, testes unitários e de
integração, debugging/profiling, ciclo em V, interesse em DO-178C. Também serve de preparação
para entrevista técnica.

## Papel do Claude: mentor, não gerador de código
- O Frederico escreve o código C++ do projeto. O Claude NÃO entrega código C++ do projeto pronto.
- O Claude pode gerar livremente: CMakeLists.txt, workflow do GitHub Actions, configuração dos
  testes, esqueleto do README (e ficheiros de configuração como .gitignore, .clang-tidy).
- Ensinar conceitos com exemplos FORA do projeto. Quando o Frederico ficar preso, dar pistas
  graduais: pergunta → nome do conceito → pseudo-código. Depois fazer code review.
- Os requisitos (REQ-xxx) são escritos pelo Frederico; o Claude revê-os.
- No fim de cada etapa, fazer 2-3 perguntas típicas de entrevista sobre o que foi usado.
- O Frederico é muito curioso: responder bem aos "porquês".
- Comunicar em português de Portugal.

## Fluxo de trabalho (simular o dia a dia de um engenheiro)
- Backlog em GitHub Issues (com critérios de aceitação e requisito associado).
- Uma branch por tarefa (ex.: feature/3-classe-bebida); nunca trabalhar na main.
- Commits pequenos em formato Conventional Commits (feat/test/fix/docs/build/ci...).
- Pull Request por branch, CI verde obrigatório, main protegida.
- O Claude faz code review dos PRs como engenheiro sénior.
- Definition of Done: compila sem avisos, testes passam e referenciam o REQ, clang-tidy limpo,
  tabela de rastreabilidade atualizada, PR revisto e merged.
- Tags no fim de cada fase: v0.1.0 (Fase A), v0.2.0 (Fase B).

## Funcionalidades
- Classe abstrata Produto (id, nome, preço) com descricao() virtual; subclasses Bebida (volume)
  e Snack (calorias).
- Stock por slot: unordered_map com unique_ptr<Produto> e quantidade.
- Interface Pagamento com pagar(valor): PagamentoMoedas (com troco), PagamentoCartao (simulado).
- MaquinaVending com padrão State: SemDinheiro, ComDinheiro, ADispensar.
- Operações: listar ordenado por preço, inserir dinheiro, selecionar slot, cancelar, reabastecer.
- Persistência do stock em CSV.

## Rigor de engenharia
1. Requisitos numerados no README (REQ-001...).
2. Cada teste referencia o requisito; tabela de rastreabilidade requisito -> teste no README.
3. GoogleTest: mínimo 10 testes unitários + 1 teste de integração (fluxo completo com gravar/carregar).
4. CMake com -Wall -Wextra -Wpedantic -Werror.
5. GitHub Actions: build, testes e clang-tidy/cppcheck em cada commit.
6. ASan + UBSan limpos; registar no README um bug real encontrado com gdb/valgrind.
7. Lógica central devolve enum class (sem exceções); documentar onde há alocação dinâmica e porquê.
8. Sem new/delete manuais, const-correctness, destrutores virtuais onde fizer sentido.

## Fases
- Fase A: repo público, CMake estrito, README com 5-8 requisitos, Produto/Bebida/Snack,
  3-5 testes rastreados, CI verde.
- Fase B: Pagamento, MaquinaVending (State), persistência, restantes testes, integração,
  sanitizers, clang-tidy, decisão de robustez e bug registado.
- Critério de pronto: o Frederico sabe explicar cada classe e requisito em voz alta e reescrever
  as partes principais sem olhar para o código.

## Checklist de conclusão da Fase A (→ tag v0.1.0)
Repositório e processo
- [ ] Repositório público no GitHub, branch main protegida (PR + CI verde obrigatórios).
- [ ] Issues da Fase A criadas; todas fechadas por PRs com merge.
- [ ] Histórico com commits pequenos em formato Conventional Commits (nada feito diretamente na main
      depois do commit inicial).
Build e qualidade
- [ ] `cmake -S . -B build -G Ninja && cmake --build build` compila do zero sem avisos
      (-Wall -Wextra -Wpedantic -Werror).
- [ ] `ctest --test-dir build --output-on-failure` passa.
- [ ] GitHub Actions verde na main (build + testes).
Código
- [ ] Produto abstrata (id, nome, preço) com descricao() virtual pura e destrutor virtual.
- [ ] Bebida (volume) e Snack (calorias) com override de descricao().
- [ ] Sem new/delete manuais; métodos de leitura const; decisão sobre a representação do preço
      tomada e justificada.
Requisitos e rastreabilidade
- [ ] README com 5-8 requisitos (REQ-001...) escritos pelo Frederico e revistos.
- [ ] 3-5 testes GoogleTest, cada um com o REQ no nome ou num comentário.
- [ ] Tabela de rastreabilidade REQ -> teste no README, sem requisitos por testar.
Aprendizagem (critério de pronto)
- [ ] O Frederico explica em voz alta: classe abstrata vs interface, virtual/override, destrutor
      virtual, const-correctness, porque o preço é representado assim, o que faz cada ficheiro
      de CMake/CI.
- [ ] Ronda de 3 perguntas de entrevista sobre a Fase A respondida.
- [ ] Tag v0.1.0 criada com notas de release.

## Ambiente
- Desenvolvimento em WSL Ubuntu-24.04, projeto em ~/projetos/vending-machine (fora do OneDrive).
- Toolchain: build-essential, cmake, ninja-build, gdb, valgrind, clang-tidy, cppcheck.
- GoogleTest via FetchContent do CMake.

## Estado atual / próximos passos
- [x] Frederico instala Ubuntu + toolchain, configura git (HTTPS com o Git Credential Manager
      do Windows) e cria repo vazio no GitHub (nome: vending-machine). Ainda não há git init local.
- [ ] Claude gera estrutura base (CMakeLists, GoogleTest, CI, .gitignore, .clang-tidy, README)
      e explica cada ficheiro; Frederico faz git init e o primeiro commit.
- [ ] Frederico escreve rascunho dos requisitos da Fase A (Produto/Bebida/Snack).
- [ ] Discussão pendente: como representar o preço (double vs inteiro em cêntimos)?
- [ ] Criar as issues da Fase A no GitHub.
