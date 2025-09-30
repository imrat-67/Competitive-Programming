import json
import os

def get_all_files(root_dir):
    """Recursively get all files from root_dir and subdirectories"""
    all_files = []
    for dirpath, dirnames, filenames in os.walk(root_dir):
        for filename in filenames:
            full_path = os.path.join(dirpath, filename)
            all_files.append(full_path)
    return all_files

def create_snippet_from_file(filepath, root_dir):
    """Create a snippet dictionary from a file"""
    with open(filepath, "r", encoding="utf-8") as f:
        lines = f.readlines()
    
    snippet_body = [line.rstrip("\n") for line in lines]
    
    # Get relative path from root_dir and use it as the snippet name
    rel_path = os.path.relpath(filepath, root_dir)
    # Remove extension for the name
    name = os.path.splitext(rel_path)[0].replace(os.sep, "_")
    
    snippet = {
        f"{name} Template": {
            "prefix": name,
            "body": snippet_body,
            "description": f"Snippet for {rel_path}"
        }
    }
    return snippet, name

def snippets_are_different(new_body, existing_body):
    """Compare two snippet bodies to check if they're different"""
    if len(new_body) != len(existing_body):
        return True
    
    for new_line, existing_line in zip(new_body, existing_body):
        if new_line != existing_line:
            return True
    
    return False

def main():
    # Configuration
    target = os.path.expanduser("~/.config/Code/User/snippets/global.code-snippets")  # Linux/macOS
    
    # Get the directory where this script is located
    script_dir = os.path.dirname(os.path.abspath(__file__))
    root_dir = script_dir  # Use script's directory as root
    
    # Create target directory if it doesn't exist
    os.makedirs(os.path.dirname(target), exist_ok=True)
    
    print(f"Scanning directory: {root_dir}")
    
    # Load existing snippets
    if os.path.exists(target):
        with open(target, "r", encoding="utf-8") as f:
            try:
                existing_snippets = json.load(f)
            except json.JSONDecodeError:
                existing_snippets = {}
    else:
        existing_snippets = {}
    
    # Get all files recursively (excluding this script itself)
    all_files = []
    script_name = os.path.basename(__file__)
    
    for filepath in get_all_files(root_dir):
        # Skip the script itself
        if os.path.basename(filepath) != script_name:
            all_files.append(filepath)
    
    if not all_files:
        print(f"No files found in {root_dir}")
        exit(0)
    
    # Process each file
    added_count = 0
    updated_count = 0
    skipped_count = 0
    
    for filepath in all_files:
        try:
            snippet, name = create_snippet_from_file(filepath, root_dir)
            snippet_key = list(snippet.keys())[0]
            new_body = snippet[snippet_key]["body"]
            
            # Check if snippet already exists
            if snippet_key in existing_snippets:
                existing_body = existing_snippets[snippet_key].get("body", [])
                
                # Compare content
                if snippets_are_different(new_body, existing_body):
                    existing_snippets.update(snippet)
                    print(f"Updated (content changed): {name}")
                    updated_count += 1
                else:
                    print(f"Skipped (no changes): {name}")
                    skipped_count += 1
            else:
                existing_snippets.update(snippet)
                print(f"Added (new): {name}")
                added_count += 1
                
        except Exception as e:
            print(f"Error processing {filepath}: {e}")
    
    # Save updated snippets
    with open(target, "w", encoding="utf-8") as f:
        json.dump(existing_snippets, f, indent=4)
    
    print(f"\n{'='*50}")
    print(f"Summary:")
    print(f"  Added: {added_count} snippets (new)")
    print(f"  Updated: {updated_count} snippets (content changed)")
    print(f"  Skipped: {skipped_count} snippets (no changes)")
    print(f"  Total files processed: {len(all_files)}")
    print(f"{'='*50}")
    print(f"\nSnippets file: {target}")

if __name__ == "__main__":
    main()