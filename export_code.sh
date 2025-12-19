#!/bin/env bash

# Nome do arquivo de saída
OUTPUT="codigo_completo.txt"

# Limpa o arquivo se ele já existir
> "$OUTPUT"

# Adiciona um cabeçalho
echo "=== CÓDIGO COMPLETO DO Miniconcha ===" >> "$OUTPUT"
echo "Gerado em: $(date)" >> "$OUTPUT"
echo "======================================" >> "$OUTPUT"
echo "" >> "$OUTPUT"

# Loop por todos os arquivos .c
for file in *.c; do
    if [ -f "$file" ]; then
        echo "/* ************************************************************************** */" >> "$OUTPUT"
        echo "/*                                                                            */" >> "$OUTPUT"
        echo "/*                                                        ARQUIVO: $file */" >> "$OUTPUT"
        echo "/*                                                                            */" >> "$OUTPUT"
        echo "/* ************************************************************************** */" >> "$OUTPUT"
        cat "$file" >> "$OUTPUT"
        echo "" >> "$OUTPUT"
        echo "" >> "$OUTPUT"
    fi
done

echo "Todos os arquivos .c foram exportados para $OUTPUT"
