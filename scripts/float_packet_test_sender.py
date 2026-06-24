#!/usr/bin/env python3
"""Send sample Task 4.1 float packets to the GUI UDP receiver."""

from __future__ import annotations

import argparse
import socket
import time


PROFILE_DEPTHS_M = [
    0.15,
    0.80,
    1.60,
    2.35,
    2.48,
    2.51,
    2.53,
    2.50,
    2.49,
    2.52,
    2.51,
    1.70,
    0.62,
    0.42,
    0.41,
    0.40,
    0.39,
    0.42,
    0.41,
    0.40,
    0.38,
    0.90,
    1.80,
    2.43,
    2.50,
    2.52,
    2.51,
    2.49,
    2.48,
    2.51,
    2.50,
    1.60,
    0.58,
    0.43,
    0.40,
    0.41,
    0.39,
    0.40,
    0.42,
    0.41,
]


def make_packet(company: str, seconds: int, depth_m: float) -> str:
    pressure_kpa = depth_m * 10.05
    return f"{company} {seconds} float {pressure_kpa:.2f} kpa {depth_m:.2f} meters"


def main() -> int:
    parser = argparse.ArgumentParser(description="Send sample float mission packets to MainUI_26.")
    parser.add_argument("--host", default="127.0.0.1", help="GUI host/IP address")
    parser.add_argument("--port", type=int, default=5007, help="GUI Float page UDP port")
    parser.add_argument("--company", default="EX01", help="Company number/code to include")
    parser.add_argument(
        "--delay",
        type=float,
        default=0.05,
        help="Seconds to wait between UDP packets",
    )
    args = parser.parse_args()

    packets = [make_packet(args.company, 0, 0.00)]
    packets.extend(make_packet(args.company, (i + 1) * 5, depth) for i, depth in enumerate(PROFILE_DEPTHS_M))

    address = (args.host, args.port)
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        for packet in packets:
            sock.sendto(packet.encode("utf-8"), address)
            print(packet)
            time.sleep(args.delay)

    print(f"Sent {len(packets)} packets to {args.host}:{args.port}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
