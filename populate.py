import os
import subprocess
from datetime import datetime, timedelta

# Configuration
repo_path = r"C:\Users\GAMER\Nearest-Neighbor-Finder"  # Use raw string to fix backslash issue
file_name = "contribution_file.txt"  # A file to modify in the repo
start_date = "2024-01-01"  # Start date for contributions (last three months)
end_date = "2024-01-10"  # End date for contributions
commits_per_day = 21  # Number of commits to make per day

def run_git_command(command, cwd):
    """Run a git command in the specified directory."""
    result = subprocess.run(command, cwd=cwd, shell=True, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"Error running command: {command}")
        print(result.stderr)
    return result.stdout

def populate_contributions():
    """Populate GitHub contribution feed with backdated commits."""
    current_date = datetime.strptime(start_date, "%Y-%m-%d")
    end = datetime.strptime(end_date, "%Y-%m-%d")
    delta = timedelta(days=1)

    while current_date <= end:
        for commit in range(commits_per_day):
            # Modify the file
            with open(os.path.join(repo_path, file_name), "a") as f:
                f.write(f"Commit on {current_date.isoformat()} - Commit #{commit + 1}\n")
            
            # Stage the file
            run_git_command("git add .", cwd=repo_path)
            
            # Commit the changes with a specific date
            commit_date = current_date.strftime("%Y-%m-%dT%H:%M:%S")
            run_git_command(f'git commit -m "Contribution on {current_date.date()}" --date "{commit_date}"', cwd=repo_path)

        # Move to the next day
        current_date += delta

    # Push changes to the remote repository
    run_git_command("git push", cwd=repo_path)
    print("Backdated contributions populated and pushed to GitHub!")

if __name__ == "__main__":
    populate_contributions()
