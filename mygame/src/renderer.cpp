// Copyright 2016 <konstruktion@gmail.com>
#include "renderer.hpp"
#include "util.hpp"


Renderer::Renderer(StaticShader* shader) {
    glm::mat4 matrix { glm::perspective(FOV, 1.0f, NEAR_PLANE, FAR_PLANE) };
    shader->use();
    shader->loadProjectionMatrix(matrix);
    shader->forgo();
}


void Renderer::prepare() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}


void Renderer::render(Entity* entity, StaticShader* shader) {
    TexturedModel * texturedModel = entity->getModel();
    RawModel * model = texturedModel->getRawModel();
    glBindVertexArray(model->getVaoId());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(
        entity->getPosition(),
        entity->getRx(),
        entity->getRy(),
        entity->getRz(),
        entity->getScale());

    shader->loadTransformationMatrix(transformationMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE0, texturedModel->getTexture()->getId());
    glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);
}
