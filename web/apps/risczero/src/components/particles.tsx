"use client";

import { useEffect, useRef } from "react";
import { useMousePosition } from "@/app/_hooks/use-mouse-position";

type Circle = {
  x: number;
  y: number;
  translateX: number;
  translateY: number;
  size: number;
  alpha: number;
  targetAlpha: number;
  dx: number;
  dy: number;
  magnetism: number;
};

type ParticlesProps = {
  className?: string;
  quantity?: number;
  staticity?: number;
  ease?: number;
  size?: number;
  vx?: number;
  vy?: number;
};

function remapValue(value: number, start1: number, end1: number, start2: number, end2: number): number {
  const remapped = ((value - start1) * (end2 - start2)) / (end1 - start1) + start2;

  return remapped > 0 ? remapped : 0;
}

export function Particles({
  className = "",
  quantity = 100,
  staticity = 50,
  ease = 50,
  size = 0.4,
  vx = 0,
  vy = 0,
}: ParticlesProps) {
  const rgb = [255, 255, 255];
  const mousePosition = useMousePosition();
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const canvasContainerRef = useRef<HTMLDivElement>(null);
  const context = useRef<CanvasRenderingContext2D | null>(null);
  const circles = useRef<Circle[]>([]);
  const mouse = useRef<{ x: number; y: number }>({ x: 0, y: 0 });
  const canvasSize = useRef<{ w: number; h: number }>({ w: 0, h: 0 });
  const dpr = typeof window === "undefined" ? 1 : window.devicePixelRatio;

  useEffect(() => {
    if (canvasRef.current) {
      context.current = canvasRef.current.getContext("2d");
    }
    initCanvas();
    animate();
    window.addEventListener("resize", initCanvas);

    return () => {
      window.removeEventListener("resize", initCanvas);
    };
  }, []);

  useEffect(() => {
    if (mousePosition.x && mousePosition.y) {
      onMouseMove();
    }
  }, [mousePosition.x, mousePosition.y]);

  function initCanvas() {
    resizeCanvas();
    drawParticles();
  }

  function onMouseMove() {
    if (canvasRef.current && mousePosition.x && mousePosition.y) {
      const rect = canvasRef.current.getBoundingClientRect();
      const { w, h } = canvasSize.current;
      const x = mousePosition.x - rect.left - w / 2;
      const y = mousePosition.y - rect.top - h / 2;
      const inside = x < w / 2 && x > -w / 2 && y < h / 2 && y > -h / 2;

      if (inside) {
        mouse.current.x = x;
        mouse.current.y = y;
      }
    }
  }

  function resizeCanvas() {
    if (!(canvasContainerRef.current && canvasRef.current && context.current)) {
      return;
    }

    circles.current.length = 0;
    canvasSize.current.w = canvasContainerRef.current.offsetWidth;
    canvasSize.current.h = canvasContainerRef.current.offsetHeight;
    canvasRef.current.width = canvasSize.current.w * dpr;
    canvasRef.current.height = canvasSize.current.h * dpr;
    canvasRef.current.style.width = `${canvasSize.current.w}px`;
    canvasRef.current.style.height = `${canvasSize.current.h}px`;
    context.current.scale(dpr, dpr);
  }

  function circleParams(): Circle {
    const x = Math.floor(Math.random() * canvasSize.current.w);
    const y = Math.floor(Math.random() * canvasSize.current.h);
    const translateX = 0;
    const translateY = 0;
    const pSize = Math.floor(Math.random() * 2) + size;
    const alpha = 0;
    const targetAlpha = Number.parseFloat((Math.random() * 0.6 + 0.1).toFixed(1));
    const dx = (Math.random() - 0.5) * 0.1;
    const dy = (Math.random() - 0.5) * 0.1;
    const magnetism = 0.1 + Math.random() * 4;

    return {
      x,
      y,
      translateX,
      translateY,
      size: pSize,
      alpha,
      targetAlpha,
      dx,
      dy,
      magnetism,
    };
  }

  function drawCircle(circle: Circle, update = false) {
    if (!context.current) {
      return;
    }

    const { x, y, translateX, translateY, size, alpha } = circle;

    context.current.translate(translateX, translateY);
    context.current.beginPath();
    context.current.arc(x, y, size, 0, 2 * Math.PI);
    context.current.fillStyle = `rgba(${rgb.join(", ")}, ${alpha})`;
    context.current.fill();
    context.current.setTransform(dpr, 0, 0, dpr, 0, 0);

    if (!update) {
      circles.current.push(circle);
    }
  }

  function clearContext() {
    if (!context.current) {
      return;
    }

    context.current.clearRect(0, 0, canvasSize.current.w, canvasSize.current.h);
  }

  function drawParticles() {
    clearContext();
    const particleCount = quantity;

    for (let i = 0; i < particleCount; i++) {
      const circle = circleParams();

      drawCircle(circle);
    }
  }

  function animate() {
    clearContext();
    circles.current.forEach((circle: Circle, i: number) => {
      // Handle the alpha value
      const edge = [
        circle.x + circle.translateX - circle.size, // distance from left edge
        canvasSize.current.w - circle.x - circle.translateX - circle.size, // distance from right edge
        circle.y + circle.translateY - circle.size, // distance from top edge
        canvasSize.current.h - circle.y - circle.translateY - circle.size, // distance from bottom edge
      ];
      const closestEdge = edge.reduce((a, b) => Math.min(a, b));
      const remapClosestEdge = Number.parseFloat(remapValue(closestEdge, 0, 20, 0, 1).toFixed(2));

      if (remapClosestEdge > 1) {
        circle.alpha = circle.alpha + 0.02;
        if (circle.alpha > circle.targetAlpha) {
          circle.alpha = circle.targetAlpha;
        }
      } else {
        circle.alpha = circle.targetAlpha * remapClosestEdge;
      }
      circle.x = circle.x + (circle.dx + vx);
      circle.y = circle.y + (circle.dy + vy);
      circle.translateX =
        circle.translateX + (mouse.current.x / (staticity / circle.magnetism) - circle.translateX) / ease;
      circle.translateY =
        circle.translateY + (mouse.current.y / (staticity / circle.magnetism) - circle.translateY) / ease;

      drawCircle(circle, true);

      // circle gets out of the canvas
      if (
        circle.x < -circle.size ||
        circle.x > canvasSize.current.w + circle.size ||
        circle.y < -circle.size ||
        circle.y > canvasSize.current.h + circle.size
      ) {
        // remove the circle from the array
        circles.current.splice(i, 1);
        // create a new circle
        const newCircle = circleParams();

        drawCircle(newCircle);
        // update the circle position
      }
    });
    window.requestAnimationFrame(animate);
  }

  return (
    <div className={className} ref={canvasContainerRef} aria-hidden="true">
      <canvas ref={canvasRef} className="size-full" />
    </div>
  );
}
