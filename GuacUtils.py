from typing import List, Optional


def guac_decode(string: str) -> Optional[List[str]]:
    """Implementation of guacamole decoder
    Example: guac_decode(\"4.chat,5.hello\") -> [\"chat\", \"hello\"]"""

    if not string:
        return []

    idx: int = 0
    distance: int
    result: List[str] = []
    chars: List[str] = list(string)

    while True:
        dist_str: str = ""

        while chars[idx].isdecimal():
            dist_str += chars[idx]
            idx = idx + 1

        if idx >= 1:
            idx -= 1

        if not dist_str.isdigit():
            return None

        distance = int(dist_str)
        idx += 1

        if chars[idx] != ".":
            return None

        idx += 1

        addition: str = ""
        for num in range(idx, idx + distance):
            addition += chars[num]

        result.append(addition)

        idx += distance
        if idx >= len(chars):
            return None

        if chars[idx] == ",":
            pass
        elif chars[idx] == ";":
            break
        else:
            return None

        idx += 1

    return result


def guac_encode(*args: str) -> str:
    """Implementation of guacamole encoder
    Example: guac_encode(\"chat\", \"hello\") -> \"4.chat,5.hello;\" """

    return f"{','.join(f'{len(arg)}.{arg}' for arg in args)};"
