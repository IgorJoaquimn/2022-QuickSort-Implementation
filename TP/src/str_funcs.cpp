#include "str_funcs.h"
extern int ordem[26];

analisador::analisador()
{
    words = new std::string[MAX];
}

void analisador::normalize(std::string &str)
// Descricao: Normalizacao da string lida;
// Entrada: str
// Saida (obrigatorio): str se torna seu equivalente normalizado;
{
    // Controle para ignorar o marcador #ORDEM;
    if(str == "#ORDEM") { str = "}"; return;}

    // Caracteres hifen soltos devem ser ignorados;
    if(str == "-") str.clear();
    
    // Cast de string para wstring para lidar com acentuacoes;
    std::wstring wide_str(str.size(), L' ');
    wide_str.resize(std::mbstowcs(&wide_str[0], str.c_str(), str.size()));

    // Nova string normalizada, comeca vazia;
    std::string n_str;
    // Variavel de controle para os casos que existem acentuacoes na palavra, se ela estiver 
    // verdadeira, o caractere atual nao deve ser inserido na normalizacao
    bool jump = 0;

    for (size_t i = 0; i < wide_str.size(); i++)
    {
        // Maiuscula para minuscula, Caso sem acentuacoes
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 'a' - 'A';

        // Maiuscula para minuscula, Caso com acentuacoes
        else if (wide_str[i] >= L'À' && wide_str[i] <= L'Ü')
            wide_str[i] += L'à' - L'À';

        // Tratamento letra A
        if (wide_str[i] >= L'à' && wide_str[i] <= L'æ')
        {
            n_str.push_back('a');
            jump = true;
        }
        // Tratamento letra E
        else if ((wide_str[i] >= L'è' && wide_str[i] <= L'ë') || wide_str[i] == L'ẽ' || wide_str[i] == L'Ẽ')
        {
            n_str.push_back('e');
            jump = true;
        }
        // Tratamento letra I
        else if ((wide_str[i] >= L'ì' && wide_str[i] <= L'ï') || wide_str[i] == L'ĩ' || wide_str[i] == L'Ĩ')
        {
            n_str.push_back('i');
            jump = true;
        }
        // Tratamento letra O
        else if (wide_str[i] >= L'ò' && wide_str[i] <= L'ö')
        {
            n_str.push_back('o');
            jump = true;
        }
        // Tratamento letra U
        else if ((wide_str[i] >= L'ù' && wide_str[i] <= L'ü') || wide_str[i] == L'ũ' || wide_str[i] == L'Ũ')
        {
            n_str.push_back('u');
            jump = true;
        }
        // Tratamento letra C
        else if (wide_str[i] == L'ç' || wide_str[i] == L'ḉ')
        {
            n_str.push_back('c');
            jump = true;
        }
        // Tratamento aspas, usado durante os testes de desempenho com textos reais.
        else if (wide_str[i] == L'“' || wide_str[i] == L'”' || wide_str[i] == L'’' || wide_str[i] == L'‘')
        {
            n_str.push_back('"');
            jump = true;
        }

        // Se o i-esimo caractere for acentuado, ele ja foi inserido, nao necessitando outra insercao
        if (!jump)
        {
            // Caracteres de pontuacao nao serao inseridos
            if (punct.find(str[i]) == std::string::npos)
                n_str.push_back(str[i]);
            jump = false;
        }
    }
    str = n_str;
}

int analisador::add(std::string &str)
// Descricao: Adiciona a nova string na lista de palavras;
// Entrada: str;
// Saida: vetor words com um novo elemento e tamanho incrementado por 1;
{
    // Apenas palavras nao vazias sao consideradas;
    if (!str.size())
        return len;

    erroAssert(MAX<1000000, "Texto com muitas palavras, risco de Stack overflow");

    // Sempre que a quantidade de palavras alcançar o maximo, o vetor dobra de tamanho;
    if (len >= MAX)
    {
        MAX *= 2;
        std::string *newArray = new std::string[MAX];
        std::string *temp     = words;
        for (int i = 0; i < len; i++)
            newArray[i] = words[i];
        words = newArray;
        delete[] temp;
    }

    // Nova palavra adicionada no vetor;
    words[len] = str;
    len++;
    ESCREVEMEMLOG((long int)(&(words[len])), sizeof(std::string), 0);
    return len;
}

void analisador::conta_palavras(std::string &output_nome)
// Descricao: Contagem de palavras repetidas e escrita do resultado no arquivo de saida;
// Entrada: output_nome: nome do arquivo a ser lido.;
// Saida: arquivo output_nome com a saida gerada;
{
    std::ofstream output;
    output.open(output_nome);
    erroAssert(output.is_open(), "Erro ao abrir arquivo de saida");

    // Variaveis para armazenar as repeticoes de cada palavara;
    // Sao dinamicos para prevenir StackOverFlow nos casos de textos extensos;
    std::string *ordered_words = new std::string[len];
    int *repetiton_words = new int[len];

    // Inicializacao dos vetores, todo texto possui ao menos uma palavra;
    ordered_words[0]    = words[0];
    repetiton_words[0]  = 1;

    // Variavel de controle que armazena quantas palavras distintas existem no texto;
    int last = 0;
    for (int i = 0; i < len - 1; i++)
    {
        LEMEMLOG((long int)(&(words[i])), sizeof(std::string), 0);
        LEMEMLOG((long int)(&(words[i + 1])), sizeof(std::string), 0);

        // Se a proxima palavra lida for diferente da atual, isso significa que ela é a atual é a ultima
        // repeticao dela mesma, logo, uma nova palavra distinta foi encotrada; 
        if (words[i] != words[i + 1])
        {
            last++;
            ordered_words[last] = words[i + 1];
            repetiton_words[last] = 1;
            ESCREVEMEMLOG((long int)(&(ordered_words[last])), sizeof(std::string), 0);
        }
        // Se nao, a proxima palavra é uma repeticao e deve ser contabilizada;
        else
        repetiton_words[last]++;
        ESCREVEMEMLOG((long int)(&(repetiton_words[last])), sizeof(int), 0);
    }

    // Escrita no arquivo de saida;
    for (int i = 0; i <= last; i++)
        output << ordered_words[i] << " " << repetiton_words[i] << std::endl;

    output << "#FIM" << std::endl;
    delete[] ordered_words;
    delete[] repetiton_words;
    output.close();
}

void analisador::start_order(int old_order[26])
// Descricao: Inicializa a nova ordem lexicografica globalmente, necessaria para a funcao isLessEqual;
// Entrada: old_order[26], nova ordem lexicografica;
// Saida: vetor ordem atualizado;
{
    *ordem = *old_order;
}

bool isLessEqual(std::string &stra, std::string &strb)
// Descricao: compara a string A com a string B em relacao a nova ordem lexicografica;
// Entrada: string A e string B;
// Saida: true se A <= B, false na congruência;
{

    // Deve-se procurar diferenças em relacao a menor palavra;
    int len = std::min(stra.length(), strb.length());

    // Para cada caractere na string A
    for (int i = 0; i < len; i++)
    {
        // Se ele for diferente do caractere da string B, deve-se retornar se esse caractere diferente é menor 
        // ou igual ao caractere em B
        if (stra[i] != strb[i])
        {
            // If ternario para garantir que caracteres fora do intervalo [a,z] sejam tratados por seu valor 
            // ASCII padrao 
            int ordera = (stra[i] >= 'a' && stra[i] <= 'z') ? ordem[stra[i] - 'a'] + 'a' : stra[i];
            int orderb = (strb[i] >= 'a' && strb[i] <= 'z') ? ordem[strb[i] - 'a'] + 'a' : strb[i];
            return ordera <= orderb;
        }
    }
    // No caso de nao existir caracteres diferentes, a menor palavra é aquela com menor tamanho. 
    return stra.length() <= strb.length();
}