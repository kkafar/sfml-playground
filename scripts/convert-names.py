#!/home/kkafara/.local/bin/python3

import pathlib as ph

figure_names = [
    'bishop', 'king', 'knight', 'pawn', 'queen', 'rook',
]


def extract_metadata(figure_name: str, figure_filename: str) -> tuple[str, str]:
    return figure_name, figure_filename[len(figure_name):]


def decode_color(code: str) -> str:
    return 'black' if code == 'B' else 'white'


def get_new_name(filename: str) -> str | None:
    for prefix in figure_names:
        if filename.startswith(prefix):
            _, metadata = extract_metadata(prefix, filename)
            if len(metadata) == 2:
                color = metadata[0]
                suffix = metadata[1]
            else:
                color = metadata[0]
                suffix = 1

            return f'{prefix}-{decode_color(color)}-{suffix}'
    return None


# Get list of all files in current dir
cwd = ph.Path.cwd()

for file in cwd.glob("*.png"):
    new_name = get_new_name(file.stem)
    if new_name is not None:
        print(f"Renaming {file.stem} to {new_name}.png")
        file.rename(f'{new_name}.png')



