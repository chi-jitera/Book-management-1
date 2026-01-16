const express = require('express');
const router = express.Router();

// Example in-memory array
let books = [
  { id: '1', title: 'Book One' },
  { id: '2', title: 'Book Two' }
];

// DELETE /api/books/:id - Remove book by ID
router.delete('/:id', (req, res) => {
  const id = req.params.id;
  const index = books.findIndex(book => book.id === id);

  if (index === -1) {
    return res.status(404).json({ error: 'Book not found' });
  }

  books.splice(index, 1);
  return res.status(204).send();
});

// Reject non-DELETE methods
router.all('/:id', (req, res) => {
  if (req.method !== 'DELETE') {
    return res.status(405).json({ error: 'Method Not Allowed' });
  }
});

module.exports = { router, books };