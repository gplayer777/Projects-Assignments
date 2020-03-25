

#define PCRE2_CODE_UNIT_WIDTH 8
#include <stdio.h>
#include <tidy/tidy.h>
#include <tidy/buffio.h>
#include <curl/curl.h>
#include <pcre.h>
#include <string.h>


#define MAX_LENGTH 200
#define OVECCOUNT 30


struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t

WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}


void downloadPicture(CURL *img, FILE *f, char str[], CURLcode imgres, int count, char Name[]){
    
    
    Name[0] = str[0]+str[1]+count;
    Name[3] = count;
    
    img = curl_easy_init();
    if(img){
        
        
        f = fopen(Name, "wb");
        if( f == NULL ) printf("%s","File cannot be opened");
        //"http://farm4.staticflickr.com/3894/15008518202_c265dfa55f_h.jpg"
        curl_easy_setopt(img, CURLOPT_URL, str);
        curl_easy_setopt(img, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(img, CURLOPT_WRITEDATA, f);
        
        
        
        imgres = curl_easy_perform(img);
        if( imgres ){
            printf("%s \n","Cannot grab the image!");
        }
    }
    
    
    curl_easy_cleanup(img);
  
    fclose(f);
    
}
char* grabWebsite(struct MemoryStruct ch, CURL *handle, CURLcode result, char websitename[] ){
    
    char*DOCUMENT;
    
    
    handle = curl_easy_init();
    //"https://pl.wikipedia.org/wiki/Wikipedia:Strona_g%C5%82%C3%B3wna"
    
   
    curl_easy_setopt(handle, CURLOPT_URL, websitename);
    

    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&ch);
    
 
    curl_easy_setopt(handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    
    result = curl_easy_perform(handle);
    
   
    if(result != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(result));
    }
    else {
        
        DOCUMENT = ch.memory;
        //printf("%s", chunk.memory);
        printf("%lu bytes retrieved\n", (unsigned long)ch.size);
    }
    
    /* cleanup curl  */
    curl_easy_cleanup(handle);
    
    free(ch.memory);
    
    return DOCUMENT;
    
}
int main(){
    
    char **subarr = malloc(100000*sizeof(char**));
    int s =0;
    CURL *image;
    CURLcode imgresult;
    FILE *fp = NULL;
    int count = 0;
    char str[MAX_LENGTH];
    char name[MAX_LENGTH] = "google.jpg";
    
    char *DOCUMENT;
    CURL *curl_handle;
    CURLcode res;
    struct MemoryStruct chunk;
    
    chunk.memory = malloc(1);
    chunk.size = 0;
    
    curl_global_init(CURL_GLOBAL_ALL);
    
    pcre *re;
    const char *error;
    char *pattern;
    char *subject;
    unsigned char *name_table;
    unsigned int option_bits;
    int erroffset;
    int find_all;
    int crlf_is_newline;
    int namecount;
    int name_entry_size;
    int ovector[OVECCOUNT];
    int subject_length;
    int rc, i;
    int utf8;
    
    pattern = "(http(s?):)([/|.|\\w|\\s|-])*\\.(?:jpg|gif|png)";
    
    
    scanf("%s", str);
    DOCUMENT = grabWebsite(chunk, curl_handle, res, str);
    printf("%s", DOCUMENT);
    subject = DOCUMENT;
    subject_length = (int)strlen(subject);
    
    
    re = pcre_compile(
                      pattern,
                      0,
                      &error,
                      &erroffset,
                      NULL);
    
    /* Compilation failed: print the error message and exit */
    
    find_all=1;
    if (re == NULL)
    {
        printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
        return 1;
    }
    
    
    rc = pcre_exec(
                   re,                   /* the compiled pattern */
                   NULL,                 /* no extra data - we didn't study the pattern */
                   subject,              /* the subject string */
                   subject_length,       /* the length of the subject */
                   0,                    /* start at offset 0 in the subject */
                   0,                    /* default options */
                   ovector,              /* output vector for substring information */
                   OVECCOUNT);           /* number of elements in the output vector */
    
    /* Matching failed: handle error cases */
    
    if (rc < 0)
    {
        switch(rc)
        {
            case PCRE_ERROR_NOMATCH: printf("No match\n"); break;
              
            default: printf("Matching error %d\n", rc); break;
        }
        pcre_free(re);             return 1;
    }
    
    /* Match succeded */
    
    printf("\nMatch succeeded at offset %d\n", ovector[0]);
    

    if (rc == 0)
    {
        rc = OVECCOUNT/3;
        printf("ovector only has room for %d captured substrings\n", rc - 1);
    }
    
    
    
    for (i = 0; i < rc; i++)
    {
        
        char *substring_start = subject + ovector[2*i];
        int substring_length = ovector[2*i+1] - ovector[2*i];
        printf("%.*s\n", substring_length, substring_start);
        
        if(i==0){
            subarr[s] = malloc(substring_length*sizeof(char));
            strncpy(subarr[s], substring_start, substring_length);
            subarr[s][substring_length] = '\0';
            s++;
        }
     
    }
    
    
    
    
  
    
    (void)pcre_fullinfo(
                        re,
                        NULL,
                        PCRE_INFO_NAMECOUNT,
                        &namecount);
    
    if (namecount <= 0) printf("No named substrings\n"); else
    {
        unsigned char *tabptr;
        printf("Named substrings\n");
        
   
        
        (void)pcre_fullinfo(
                            re,
                            NULL,
                            PCRE_INFO_NAMETABLE,
                            &name_table);
        
        (void)pcre_fullinfo(
                            re,
                            NULL,
                            PCRE_INFO_NAMEENTRYSIZE,
                            &name_entry_size);
        
       
        
        tabptr = name_table;
        for (i = 0; i < namecount; i++)
        {
            int n = (tabptr[0] << 8) | tabptr[1];
            printf("(%d) %*s: %.*s\n", n, name_entry_size - 3, tabptr + 2,
                   ovector[2*n+1] - ovector[2*n], subject + ovector[2*n]);
            tabptr += name_entry_size;
        }
    }
        if (!find_all)
    {
        pcre_free(re);   /* Release the memory used for the compiled pattern */
        return 0;
    }
    
    (void)pcre_fullinfo(re, NULL, PCRE_INFO_OPTIONS, &option_bits);
    utf8 = option_bits & PCRE_UTF8;
    option_bits &= PCRE_NEWLINE_CR|PCRE_NEWLINE_LF|PCRE_NEWLINE_CRLF|
    PCRE_NEWLINE_ANY|PCRE_NEWLINE_ANYCRLF;
    
   
    if (option_bits == 0)
    {
        int d;
        (void)pcre_config(PCRE_CONFIG_NEWLINE, &d);
        
        option_bits = (d == 13)? PCRE_NEWLINE_CR :
        (d == 10)? PCRE_NEWLINE_LF :
        (d == (13<<8 | 10))? PCRE_NEWLINE_CRLF :
        (d == -2)? PCRE_NEWLINE_ANYCRLF :
        (d == -1)? PCRE_NEWLINE_ANY : 0;
    }
    
    
    
    crlf_is_newline =
    option_bits == PCRE_NEWLINE_ANY ||
    option_bits == PCRE_NEWLINE_CRLF ||
    option_bits == PCRE_NEWLINE_ANYCRLF;
    
    /* Loop for second and subsequent matches */
    
    for (;;)
    {
        int options = 0;                 /* Normally no options */
        int start_offset = ovector[1];   /* Start at end of previous match */
        

        
        if (ovector[0] == ovector[1])
        {
            if (ovector[0] == subject_length) break;
            options = PCRE_NOTEMPTY_ATSTART | PCRE_ANCHORED;
        }
        
        /* Run the next matching operation */
        
        rc = pcre_exec(
                       re,                   /* the compiled pattern */
                       NULL,                 /* no extra data - we didn't study the pattern */
                       subject,              /* the subject string */
                       subject_length,       /* the length of the subject */
                       start_offset,         /* starting offset in the subject */
                       options,              /* options */
                       ovector,              /* output vector for substring information */
                       OVECCOUNT);           /* number of elements in the output vector */
        
      
        
        if (rc == PCRE_ERROR_NOMATCH)
        {
            if (options == 0) break;                    /* All matches found */
            ovector[1] = start_offset + 1;              /* Advance one byte */
            if (crlf_is_newline &&                      /* If CRLF is newline & */
                start_offset < subject_length - 1 &&    /* we are at CRLF, */
                subject[start_offset] == '\r' &&
                subject[start_offset + 1] == '\n')
                ovector[1] += 1;                          /* Advance by one more. */
            else if (utf8)                              /* Otherwise, ensure we */
            {                                         /* advance a whole UTF-8 */
                while (ovector[1] < subject_length)       /* character. */
                {
                    if ((subject[ovector[1]] & 0xc0) != 0x80) break;
                    ovector[1] += 1;
                }
            }
            continue;    /* Go round the loop again */
        }
        
        /* Other matching errors are not recoverable. */
        
        if (rc < 0)
        {
            printf("Matching error %d\n", rc);
            pcre_free(re);    /* Release memory used for the compiled pattern */
            return 1;
        }
        
        /* Match succeded */
        
        printf("\nMatch succeeded again at offset %d\n", ovector[0]);
        
        /* The match succeeded, but the output vector wasn't big enough. */
        
        if (rc == 0)
        {
            rc = OVECCOUNT/3;
            printf("ovector only has room for %d captured substrings\n", rc - 1);
        }
        
       
        
        for (i = 0; i < rc; i++)
        {
            char *substring_start = subject + ovector[2*i];
            int substring_length = ovector[2*i+1] - ovector[2*i];
            printf("%2d: %.*s\n", i, substring_length, substring_start);
            
            if(i==0){
                subarr[s] = malloc(substring_length*sizeof(char));
                strncpy(subarr[s], substring_start, substring_length);
                subarr[s][substring_length] = '\0';
                s++;
            }
           
        }
        
        if (namecount <= 0) printf("No named substrings\n"); else
        {
            unsigned char *tabptr = name_table;
            printf("Named substrings\n");
            for (i = 0; i < namecount; i++)
            {
                int n = (tabptr[0] << 8) | tabptr[1];
                printf("(%d) %*s: %.*s\n", n, name_entry_size - 3, tabptr + 2,
                       ovector[2*n+1] - ovector[2*n], subject + ovector[2*n]);
                tabptr += name_entry_size;
            }
        }
    }
    
    for(int i =0;i<s;i++){
        
        downloadPicture(image, fp, subarr[i], imgresult, i, name);
        
    }
       // printf("%s \n", subarr[i]);
    
    
    printf("\n");
    pcre_free(re);
    
    
    
    
    curl_global_cleanup();
    
    
    
    return 0;
}
