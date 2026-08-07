<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Book Management Form</title>
    <style>
        /* Add your styles here */
        .form-group {
            margin-bottom: 15px;
        }
        label {
            display: block;
            margin-bottom: 5px;
        }
        input, select {
            width: 100%;
            padding: 8px;
            box-sizing: border-box;
        }
        button {
            margin-top: 10px;
            padding: 10px 15px;
            background-color: #007BFF;
            color: white;
            border: none;
            cursor: pointer;
        }
        .error {
            color: red;
        }
    </style>
</head>
<body>
    <h1>Book Management Form</h1>
    <form id="bookForm">
        <div class="form-group">
            <label for="title">Title</label>
            <input type="text" id="title" name="title" required>
        </div>
        <div class="form-group">
            <label for="author">Author</label>
            <input type="text" id="author" required>
        </div>
        <div class="form-group">
            <label for="publishedYear">Published Year</label>
            <input type="number" id="publishedYear" required>
        </div>
        <div class="form-group">
            <label for="genre">Genre</label>
            <input type="text" id="genre" required>
        </div>
        <div class="form-group">
            <label for="available">Available</label>
            <select id="available" required>
                <option value="true">Yes</option>
                <option value="false">No</option>
            </select>
        </div>
        <button type="submit">Submit</button>
    </form>
    <div id="error" class="error"></div>

    <script>
        document.getElementById('bookForm').addEventListener('submit', async function(event) {
            event.preventDefault();
            const title = document.getElementById('title').value;
            const author = document.getElementById('author').value;
            const publishedYear = document.getElementById('publishedYear').value;
            const genre = document.getElementById('genre').value;
            const available = document.getElementById('available').value === 'true';

            const bookData = { title, author, publishedYear, genre, available };

            try {
                const response = await fetch('/api/books', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                    },
                    body: JSON.stringify(bookData),
                });

                if (!response.ok) {
                    throw new Error('Failed to create book');
                }

                const result = await response.json();
                alert('Book created successfully!');
                console.log(result);
            } catch (error) {
                console.error('Error:', error);
                document.getElementById('error').textContent = 'Error creating book: ' + error.message;
            }
        });
    </script>
</body>
</html>
