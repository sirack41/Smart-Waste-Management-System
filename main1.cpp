const express = require('express');
const bodyParser = require('body-parser');
const mongoose = require('mongoose');
const app = express();

app.use(bodyParser.urlencoded({ extended: true }));

mongoose.connect('mongodb://localhost:27017/smartwaste', { useNewUrlParser: true });

const Bin = mongoose.model('Bin', {
  bin_id: String,
  level: Number,
  timestamp: { type: Date, default: Date.now }
});

app.post('/upload', async (req, res) => {
  const { bin_id, level } = req.body;
  const binData = new Bin({ bin_id, level });
  await binData.save();
  res.send('OK');
});

app.listen(3000, () => {
  console.log('Server running on port 3000');
});
