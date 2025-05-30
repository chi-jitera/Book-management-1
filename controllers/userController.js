const userService = require('../services/userService');

exports.login = async (req, res) => {
    try {
        const { username, password } = req.body;
        const user = await userService.authenticateUser(username, password);
        res.status(200).json({ message: 'Login successful', user });
    } catch (error) {
        res.status(401).json({ error: error.message });
    }
};

exports.register = async (req, res) => {
    try {
        const user = await userService.createUser(req.body);
        res.status(201).json({ message: 'User registered successfully', user });
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};