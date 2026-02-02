const authorService = require('../services/authorService');

exports.createAuthor = async (req, res) => {
  try {
    const author = await authorService.createAuthor(req.body);
    res.status(201).json(author);
  } catch (error) {
    res.status(400).json({ error: error.message });
  }
};

exports.getAllAuthors = async (req, res) => {
  const authors = await authorService.getAllAuthors();
  res.json(authors);
};

exports.getAuthorById = async (req, res) => {
  try {
    const author = await authorService.getAuthorById(req.params.id);
    if (!author) {
      return res.status(404).json({ error: 'Author not found' });
    }
    res.json(author);
  } catch (error) {
    res.status(404).json({ error: error.message });
  }
};

exports.updateAuthor = async (req, res) => {
  try {
    const author = await authorService.updateAuthor(req.params.id, req.body);
    res.json(author);
  } catch (error) {
    res.status(400).json({ error: error.message });
  }
};

exports.patchAuthor = async (req, res) => {
  try {
    const author = await authorService.patchAuthor(req.params.id, req.body);
    res.json(author);
  } catch (error) {
    const status = error.message === 'Author not found' ? 404 : 400;
    res.status(status).json({ error: error.message });
  }
};

exports.deleteAuthor = async (req, res) => {
  try {
    const author = await authorService.deleteAuthor(req.params.id);
    if (!author) {
      return res.status(404).json({ error: 'Author not found' });
    }
    res.json({ message: 'Author deleted' });
  } catch (error) {
    res.status(404).json({ error: error.message });
  }
};