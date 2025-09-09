// scripts/encrypt.js
const fs = require('fs');
const path = require('path');
const { execFileSync } = require('child_process');
const crypto = require('crypto');
const cheerio = require('cheerio'); // npm i cheerio

const SITE_DIR = path.resolve('_site');

function* walk(dir) {
  for (const e of fs.readdirSync(dir, { withFileTypes: true })) {
    const p = path.join(dir, e.name);
    if (e.isDirectory()) yield* walk(p);
    else if (e.isFile() && p.endsWith('.html')) yield p;
  }
}

for (const file of walk(SITE_DIR)) {
  const html = fs.readFileSync(file, 'utf8');
  const $ = cheerio.load(html);

  // 포스트별 비번: 메타에 있으면 이 파일만 암호화
  const password = $('meta[name="private-password"]').attr('content');
  if (!password) continue;

  // (선택) 커스터마이즈 가능: 힌트/타이틀/버튼 텍스트 등 메타로 전달 가능
  const title = $('meta[name="private-title"]').attr('content') || 'Protected';
  const remember = $('meta[name="private-remember"]').attr('content') === 'true'; // 기본 false
  const salt = crypto.randomBytes(16).toString('hex'); // 파일마다 다른 솔트

  try {
    execFileSync('npx', [
      'staticrypt', file, password,
      '--output', file,
      '--title', title,
      '--short',
      '--no-banner',
      '--salt', salt,
      ...(remember ? ['--remember'] : [])
    ], { stdio: 'inherit' });
    console.log('Encrypted:', path.relative(SITE_DIR, file));
  } catch (e) {
    console.error('Encrypt failed:', path.relative(SITE_DIR, file), e.message);
    // 실패해도 다른 파일 계속
  }
}
