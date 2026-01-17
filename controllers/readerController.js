const readerService = require('../services/readerService');

exports.createReader = async (req, res) => {
    try {
        const reader = await readerService.createReader(req.body);
        res.status(201).json(reader);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};

exports.getReaders = async (req, res) => {
    try {
        const readers = await readerService.getReaders();
        res.json(readers);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};

exports.getReaderById = async (req, res) => {
    try {
        const reader = await readerService.getReaderById(req.params.id);
        if (!reader) {
            return res.status(404).json({ error: 'Reader not found' });
        }
        res.json(reader);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};

exports.updateReader = async (req, res) => {
    try {
        const reader = await readerService.updateReader(req.params.id, req.body);
        if (!reader) {
            return res.status(404).json({ error: 'Reader not found' });
        }
        res.json(reader);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};

exports.deleteReader = async (req, res) => {
    try {
        const reader = await readerService.deleteReader(req.params.id);
        if (!reader) {
            return res.status(404).json({ error: 'Reader not found' });
        }
        res.status(204).send();
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};
