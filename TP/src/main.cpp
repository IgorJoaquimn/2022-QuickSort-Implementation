#include <iostream>
#include <fstream>
#include <locale.h>
#include <getopt.h>
#include "memlog.h"
#include "msgassert.h"
#include "str_funcs.h"

int ordem[26] = {0};
std::string input_nome;
std::string output_nome;
int mediana = 0, size_partition = 0;

analisador analisador;

void parse_args(int argc, char **argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida (obrigatorio): input_nome,output_nome,mediana,size
{
    // variaveis externas do getopt
    extern char *optarg;
    char c;

    while ((c = getopt(argc, argv, "i:I:o:O:m:M:s:S:")) != EOF)
        switch (c)
        {
        case 'i':
        case 'I':
            input_nome = optarg;
            break;
        case 'o':
        case 'O':
            output_nome = optarg;
            break;
        case 'm':
        case 'M':
            mediana = std::stoi(optarg);
            break;
        case 's':
        case 'S':
            size_partition = std::stoi(optarg);
            break;
        default:
            return;
        }
}

void leitura_arquivo(std::ifstream &input)
// Descricao: leitura do arquivo recebido por linha de parâmetro
// Entrada: input: arquivo carregado
// Saida (obrigatorio): lista de palavras do texto armazenadas na estrutura analisador.words;
{
    std::string buffer, aux;
    while (input >> buffer)
    {
        if (buffer == "#TEXTO")
        {
            // Enquanto for possivel ler da entrada e ela nao for o marcador #ORDEM, faça:
            // A variável "aux" ser igual a "}" é um controle para nao concatenar a 
            // #ORDEM na lista de palavras 
            while (input >> buffer && buffer != "#ORDEM" && aux != "}")
            {
                analisador.normalize(buffer);
                if ((buffer.back() == '-'))
                {
                    input >> aux;
                    analisador.normalize(aux);
                    buffer.append(aux);
                    analisador.normalize(buffer);
                }
                analisador.add(buffer);
            }
        }

        if (buffer == "#ORDEM" || aux == "}")
        // #ORDEM -> Leitura das 26 letras do alfabeto
        {
            char letter;
            for (int i = 0; i < 26; i++)
            {
                input >> letter;
                ordem[letter - 'A'] = i;
            }
        }
    }
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    
    // Abertura de arquivos de entrada/saida e leitura da linha de comandos;
    std::ifstream input;
    parse_args(argc, argv);
    input.open(input_nome);
    erroAssert(input.is_open(), "Erro ao abrir arquivo de entrada");

    // Leitura do texto a ser ordenado e da ordem lexicografica;
    defineFaseMemLog(0);
    leitura_arquivo(input);
    analisador.start_order(ordem);

    // Ordenacao;
    defineFaseMemLog(1);
    quicksort(analisador.words, 0, analisador.len - 1, size_partition, mediana);

    // Contagem e escrita em arquivo de saida;
    defineFaseMemLog(2);
    analisador.conta_palavras(output_nome);

    input.close();
    delete[] analisador.words;
    return 0;
}
