const readerService = require('../services/readerService');

exports.createReader = async (req, res) => {
    try {
        const reader = await readerService.createReader(req.body);
        res.status(201).json(reader);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};

exports.getReaderById = async (req, res) => {
    try {
        const reader = await readerService.getReaderById(req.params.id);
        res.json(reader);
    } catch (error) {
        res.status(404).json({ error: error.message });
    }
};

exports.updateReader = async (req, res) => {
    try {
        const reader = await readerService.updateReader(req.params.id, req.body);
        res.json(reader);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};

exports.deleteReader = async (req, res) => {
    try {
        const message = await readerService.deleteReader(req.params.id);
        res.json(message);
    } catch (error) {
        res.status(404).json({ error: error.message });
    }
};
