export type DefaultNotionProperties = {
  id?: string;
  date?: { start_date?: string; time_zone?: string; start_time?: string };
  slug?: string;
  tags?: string[];
  summary?: string;
  title?: string;
  author?: string[];
  status?: ["Published" | "Draft"] | string[];
};

export type Post = Omit<DefaultNotionProperties, "tags"> & {
  postDate: number;
  tags: {
    tag: string;
  }[];
  pageCover: string;
};

export type Project = Omit<DefaultNotionProperties, "date" | "tags"> & {
  tags: {
    tag: string;
  }[];
  pageCover: string;
};

export type Leadership = Omit<DefaultNotionProperties, "date" | "tags"> & {
  pageCover: string;
  twitter?: string;
  linkedin?: string;
};

export type Investor = Omit<DefaultNotionProperties, "date" | "tags"> & {
  pageCover: string;
};
