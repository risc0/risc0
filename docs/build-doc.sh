# Requires:
# brew: pandoc, mermaid-cli
# pip: pandoc-mermaid-filter 
MERMAID_BIN=mmdc pandoc battleship_rust_tutorial.md -o battleship_rust_tutorial.html --filter pandoc-mermaid --standalone

