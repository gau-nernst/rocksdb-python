import argparse
import json
import subprocess


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--name", required=True)
    args = parser.parse_args()

    cmd = 'gh api -H "Accept: application/vnd.github.v3+json" /repos/gau-nernst/rocksdb-python/actions/artifacts'
    proc = subprocess.run(cmd, shell=True, capture_output=True)
    resp = json.loads(proc.stdout)

    art_id = None
    for art in resp["artifacts"]:
        if art["name"] == args.name:
            art_id = art["id"]
            break
    assert art_id is not None, f"Artifact {args.name} not found"
    subprocess.run(f"{cmd}/{art_id}/zip > artifact.zip", shell=True)


if __name__ == "__main__":
    main()
