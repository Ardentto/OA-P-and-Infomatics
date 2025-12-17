CREATE TABLE students (
    student_id SERIAL PRIMARY KEY,
    full_name VARCHAR(100) NOT NULL,
    group_number VARCHAR(10) NOT NULL
);

CREATE TABLE subjects (
    subject_id SERIAL PRIMARY KEY,
    subject_name VARCHAR(100) NOT NULL
);

CREATE TABLE grades (
    grade_id SERIAL PRIMARY KEY,
    student_id INTEGER REFERENCES students(student_id),
    subject_id INTEGER REFERENCES subjects(subject_id),
    grade INTEGER CHECK (grade BETWEEN 1 AND 5),
    grade_date DATE DEFAULT CURRENT_DATE
);

CREATE TABLE attendance (
    attendance_id SERIAL PRIMARY KEY,
    student_id INTEGER REFERENCES students(student_id),
    date_attended DATE NOT NULL,
    status VARCHAR(10) CHECK (status IN ('present', 'absent', 'ill'))
);

CREATE TABLE notes (
    note_id SERIAL PRIMARY KEY,
    student_id INTEGER REFERENCES students(student_id),
    note_text TEXT,
    note_tsvector TSVECTOR GENERATED ALWAYS AS (to_tsvector('russian', note_text)) STORED
);

INSERT INTO students (full_name, group_number) VALUES
('Иванов Иван Иванович', 'БМТ-101'),
('Петров Петр Петрович', 'БМТ-101'),
('Сидоров Алексей Викторович', 'БМТ-101'),
('Кузнецова Мария Сергеевна', 'БМТ-101'),
('Смирнов Дмитрий Алексеевич', 'БМТ-101'),
('Васильева Анна Павловна', 'БМТ-101');

INSERT INTO subjects (subject_name) VALUES
('Математический анализ'),
('Аналитическая геометрия'),
('Информатика');

DO $$
DECLARE
    student RECORD;
    subject RECORD;
BEGIN
    FOR student IN SELECT student_id FROM students LOOP
        FOR subject IN SELECT subject_id FROM subjects LOOP
            INSERT INTO grades (student_id, subject_id, grade)
            VALUES (
                student.student_id, 
                subject.subject_id,
                floor(random() * 4 + 2)::INTEGER
            );
        END LOOP;
    END LOOP;
END $$;

INSERT INTO attendance (student_id, date_attended, status)
SELECT 
    student_id,
    DATE '2024-01-10',
    CASE 
        WHEN random() < 0.8 THEN 'present'
        WHEN random() < 0.9 THEN 'ill'
        ELSE 'absent'
    END
FROM students
UNION ALL
SELECT 
    student_id,
    DATE '2024-01-12',
    CASE 
        WHEN random() < 0.85 THEN 'present'
        WHEN random() < 0.95 THEN 'ill'
        ELSE 'absent'
    END
FROM students;

INSERT INTO notes (student_id, note_text) VALUES
(1, 'Любит информатику, всегда активно участвует на занятиях'),
(2, 'Нужна помощь по информатике, особенно в программировании'),
(3, 'Редко посещает занятия по информатике, но выполняет все задания'),
(4, 'Отличник по всем предметам, особенно силен в математике'),
(5, 'Хорошо работает в команде над проектами по информатике'),
(6, 'Прогресс по информатике заметен, улучшил оценки с 3 до 4');

CREATE INDEX idx_students_group ON students(group_number);
CREATE INDEX idx_grades_student ON grades(student_id);
CREATE INDEX idx_notes_fts ON notes USING GIN(note_tsvector);

CREATE VIEW student_avg_grades AS
SELECT 
    s.student_id,
    s.full_name,
    s.group_number,
    ROUND(AVG(g.grade)::NUMERIC, 2) as average_grade,
    COUNT(g.grade_id) as total_grades
FROM students s
LEFT JOIN grades g ON s.student_id = g.student_id
GROUP BY s.student_id, s.full_name, s.group_number;

BEGIN;
INSERT INTO students (full_name, group_number) 
VALUES ('Новиков Андрей Сергеевич', 'БМТ-101');

DO $$
DECLARE
    new_student_id INTEGER;
BEGIN
    SELECT student_id INTO new_student_id 
    FROM students 
    WHERE full_name = 'Новиков Андрей Сергеевич';
    
    INSERT INTO grades (student_id, subject_id, grade) VALUES
    (new_student_id, 1, 4),
    (new_student_id, 2, 5),
    (new_student_id, 3, 4);
    
    INSERT INTO attendance (student_id, date_attended, status)
    VALUES (new_student_id, '2024-01-15', 'present');
    
    INSERT INTO notes (student_id, note_text)
    VALUES (new_student_id, 'Новый студент, показывает хорошие результаты по информатике');
END $$;
COMMIT;

WITH target_student AS (
    SELECT student_id, group_number 
    FROM students 
    WHERE full_name = 'Петров Петр Петрович'
)
SELECT 
    s.student_id,
    s.full_name,
    s.group_number
FROM students s
WHERE s.group_number = (SELECT group_number FROM target_student)
ORDER BY s.student_id
LIMIT 5;

SELECT * FROM student_avg_grades 
WHERE full_name = 'Иванов Иван Иванович';

SELECT 
    s.subject_name,
    ROUND(AVG(g.grade)::NUMERIC, 2) as avg_grade,
    COUNT(g.grade_id) as total_grades,
    MIN(g.grade) as min_grade,
    MAX(g.grade) as max_grade
FROM subjects s
JOIN grades g ON s.subject_id = g.subject_id
WHERE s.subject_name = 'Информатика'
GROUP BY s.subject_id, s.subject_name;

SELECT 
    n.note_id,
    s.full_name,
    n.note_text
FROM notes n
JOIN students s ON n.student_id = s.student_id
WHERE n.note_tsvector @@ to_tsquery('russian', 'Информатика');

BEGIN;
UPDATE attendance 
SET status = 'present'
WHERE student_id = 1 
AND date_attended = '2024-01-10';
COMMIT;