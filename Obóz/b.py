ascii_room = [
    ".*...",
    ".*#..",
    ".*...",
    ".*.##",
    ".***.",
    "##.*.",
    "****.",
    "k...."
]

cell_size = 0.5

def ascii_to_tikz_krzys(ascii_room):
    rows = len(ascii_room)
    cols = max(len(r) for r in ascii_room)
    W = cols * cell_size
    H = rows * cell_size

    tikz = []
    tikz.append("\\begin{tikzpicture}")
    tikz.append(f"\\useasboundingbox (0,0) rectangle ({W},{H});")
    tikz.append(f"\\draw[black, thick] (0,0) rectangle ({W},{H});")

    # Rysowanie pól
    for y, row in enumerate(ascii_room):
        for x, ch in enumerate(row):
            tikz_x = x * cell_size
            tikz_y = (rows - 1 - y) * cell_size

            if ch == "#":
                tikz.append(
                    f"\\filldraw[black] ({tikz_x},{tikz_y}) rectangle "
                    f"({tikz_x + cell_size},{tikz_y + cell_size});"
                )
            else:
                tikz.append(
                    f"\\draw[gray] ({tikz_x},{tikz_y}) rectangle "
                    f"({tikz_x + cell_size},{tikz_y + cell_size});"
                )

    # Łączenie gwiazdek czerwoną kreską (tylko sąsiedzi bokiem)
    for y, row in enumerate(ascii_room):
        for x, ch in enumerate(row):
            if ch == "*":
                for dx, dy in [(1, 0), (0, 1)]:  # prawo i dół, żeby nie dublować
                    nx, ny = x + dx, y + dy
                    if 0 <= ny < rows and 0 <= nx < len(ascii_room[ny]):
                        if ascii_room[ny][nx] == "*":
                            x1 = x * cell_size + cell_size / 2
                            y1 = (rows - 1 - y) * cell_size + cell_size / 2
                            x2 = nx * cell_size + cell_size / 2
                            y2 = (rows - 1 - ny) * cell_size + cell_size / 2

                            tikz.append(
                                f"\\draw[red, very thick] ({x1},{y1}) -- ({x2},{y2});"
                            )

    # Rysowanie Krzysia (k) jako niebieskiej kuleczki
    for y, row in enumerate(ascii_room):
        for x, ch in enumerate(row):
            if ch == "k":
                cx = x * cell_size + cell_size / 2
                cy = (rows - 1 - y) * cell_size + cell_size / 2
                tikz.append(f"\\fill[blue] ({cx},{cy}) circle (0.12);")

    tikz.append("\\end{tikzpicture}")
    return "\n".join(tikz)


print(ascii_to_tikz_krzys(ascii_room))
