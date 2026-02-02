const express = require('express');
const router = express.Router();
const authorController = require('../controllers/authorController');

// Create an author
router.post('/', authorController.createAuthor);

// Get all authors
router.get('/', authorController.getAllAuthors);

// Get author by ID
router.get('/:id', authorController.getAuthorById);

// Update author (full)
router.put('/:id', authorController.updateAuthor);

// Update author (partial)
router.patch('/:id', authorController.patchAuthor);

// Delete author
router.delete('/:id', authorController.deleteAuthor);

module.exports = router;