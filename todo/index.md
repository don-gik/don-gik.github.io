---
layout: default
title: To‑Do
description: 할 일 목록
permalink: /todo/
---

{% assign tasks = site.data.todo.tasks | default: site.data.todo %}
{% if tasks == nil %}{% assign tasks = '' | split: '' %}{% endif %}
{% assign open = tasks | where_exp: 'item', 'item.done != true' %}
{% assign completed = tasks | where_exp: 'item', 'item.done == true' %}

<section class="todo" aria-labelledby="todo-title">
  <h1 id="todo-title" class="todo__title">To Do</h1>

  <div class="todo__controls">
    <span class="todo__count"><strong>{{ open | size }}</strong>개 남음</span>
    <span class="muted">전체 {{ tasks | size }}개 · 완료 {{ completed | size }}개</span>
  </div>

  <h2>미완료</h2>
  <ul class="todo__list">
    {% if open.size == 0 %}
      <li class="todo__empty">미완료 항목이 없습니다.</li>
    {% else %}
      {% for item in open %}
        <li class="todo__item">
          <label class="todo__label">
            <input type="checkbox" class="todo__toggle" disabled>
            <span class="todo__text">{{ item.title }}</span>
          </label>
          {% if item.due or item.note %}
            <span class="muted">
              {% if item.due %}마감 {{ item.due | date: '%Y-%m-%d' }}{% endif %}
              {% if item.note %}{% if item.due %} · {% endif %}{{ item.note }}{% endif %}
            </span>
          {% endif %}
        </li>
      {% endfor %}
    {% endif %}
  </ul>

  <details>
    <summary>완료됨 {{ completed | size }}개</summary>
    <ul class="todo__list" style="margin-top: .8rem;">
      {% if completed.size == 0 %}
        <li class="todo__empty">완료된 항목이 없습니다.</li>
      {% else %}
        {% for item in completed %}
          <li class="todo__item is-completed">
            <label class="todo__label">
              <input type="checkbox" class="todo__toggle" checked disabled>
              <span class="todo__text">{{ item.title }}</span>
            </label>
            {% if item.due or item.note %}
              <span class="muted">
                {% if item.due %}마감 {{ item.due | date: '%Y-%m-%d' }}{% endif %}
                {% if item.note %}{% if item.due %} · {% endif %}{{ item.note }}{% endif %}
              </span>
            {% endif %}
          </li>
        {% endfor %}
      {% endif %}
    </ul>
  </details>
</section>
