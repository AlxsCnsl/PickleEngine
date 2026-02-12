import re

def to_snake_case(text):
    text = re.sub(r'[\s\-]+', '_', text) 
    text = re.sub(r'([A-Z]+)', r'_\1', text)
    text = text.lower()
    text = re.sub(r'^_|_$', '', text)
    text = re.sub(r'__+', '_', text)
    return text
